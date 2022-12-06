#include "ClientManager.h"

ClientManager::ClientManager(uint8_t &id, Socket &aClient, GameManager &aGameManager) :
        client(std::move(aClient)),
        gameManager(aGameManager),
        closed(false),
        id(id),
        shouldContinueLooping(true), notConnectedToGame(true){}

void ClientManager::run() {
    ServerProtocolo protocolo;
    try {
        std::function<void(void *, int)> recvCallable =
                std::bind(&ClientManager::receiveBytes, this, std::placeholders::_1, std::placeholders::_2);

        std::function<void(void *, unsigned int)> sendCallable =
                std::bind(&ClientManager::sendBytes, this, std::placeholders::_1, std::placeholders::_2);

        std::function<void(ProtectedQueue<std::shared_ptr<ServerAction>> *,
                           BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>> *)> startThreadsCallable =
                std::bind(&ClientManager::startClientThreads, this, std::placeholders::_1, std::placeholders::_2);

        while (this->shouldContinueLooping) {
            uint8_t actionType = 0x0;
            if (this->client.recvall(&actionType, sizeof(actionType), &closed) <= 0) {
                throw LibError(1, "Client disconnected");
            }
            auto actionCommand = protocolo.deserializeDataOnCommand(actionType, id,
                                                                    gameManager,
                                                                    recvCallable,
                                                                    sendCallable,
                                                                    startThreadsCallable);
            actionCommand->execute(startThreadsCallable, sendCallable, protocolo);
        }
    } catch (const LibError &e) {
            notConnectedToGame = true;
            return;

    } catch (...) {}
    waitClientThreads();
}

void ClientManager::receiveBytes(void *bytes_to_receive, int sizeToReceive) {
    this->client.recvall(bytes_to_receive, sizeToReceive, &closed);
}

void ClientManager::sendBytes(void* bytes_to_send, unsigned int size) {
    if(!closed) {
        this->client.sendall(bytes_to_send, size, &closed);
    }
}

void ClientManager::waitClientThreads() {
    notConnectedToGame = false;
    clientReceiverThread->join();
    clientSenderThread->join();
    gameManager.deletePlayer(id);
    delete clientReceiverThread;
    delete clientSenderThread;
    closed = true;
}

void ClientManager::startClientThreads(ProtectedQueue<std::shared_ptr<ServerAction>> *qReceiver,
                                       BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>> *senderQueue) {
    //qReceiver -> ServerAction
    //senderQueue -> ServerUpdate
    this->shouldContinueLooping = false;
    clientReceiverThread = new ClientReceiver(client, qReceiver, id);
    clientSenderThread = new ClientSender(client, senderQueue, id);
    std::cout << "Starting client threads" << std::endl;
    clientReceiverThread->start();
    clientSenderThread->start();
}

void ClientManager::endManager() {
    try {
        client.shutdown(2);
        client.close();
        if (NotConnectedToGame()) {
            return;
        }
        clientReceiverThread->stop();
        clientSenderThread->stop();
    } catch (...) {
        return;
    }
}

uint8_t ClientManager::getId() {
    return id;
}
bool ClientManager::NotConnectedToGame() {
    return notConnectedToGame;
}

void ClientManager::stop() {
    endManager();
}

ClientManager::~ClientManager() {}

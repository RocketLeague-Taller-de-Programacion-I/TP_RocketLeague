#include "ClientManager.h"

ClientManager::ClientManager(uint8_t &id, Socket &aClient, GameManager &aGameManager) :
        client(std::move(aClient)),
        gameManager(aGameManager),
        closed(false),
        id(id),
        shouldContinueLooping(true){}

void ClientManager::run() {
    ServerProtocolo protocolo;
    try {
        std::function<void(void *, int )> recvCallable =
                std::bind(&ClientManager::receiveBytes, this, std::placeholders::_1 ,std::placeholders::_2);

        std::function<void(void*, unsigned int)> sendCallable =
                std::bind(&ClientManager::sendBytes, this, std::placeholders::_1, std::placeholders::_2);

        std::function<void(ProtectedQueue<std::shared_ptr<ServerAction>> *,
                BlockingQueue<std::shared_ptr<ServerUpdate>> *)> startThreadsCallable =
                std::bind(&ClientManager::startClientThreads, this, std::placeholders::_1, std::placeholders::_2);

        while (this->shouldContinueLooping) {
            uint8_t actionType = 0x0;
            this->client.recvall(&actionType, sizeof(actionType), &closed);
                  // actionCommand será alguno de los comandos (ActionCreate, ActionJoin, ActionList)
                    // cuando se crea, recibe al GameManager (entonces sabe a que metodo de ese monitor llamar)
                    // deserializeDataOnCommand recibe el opcode del comando (un byte) y switchea sobre el mismo
                    // El protocolo tiene acceso a recvCallable para recibir el resto del payload del comando y poder crearlo
                    // Si hay que enviarle una rta. al cliente, hacemos uso del sendCallable!
            auto actionCommand = protocolo.deserializeDataOnCommand(actionType, id,
                                                                           gameManager,
                                                                           recvCallable,
                                                                           sendCallable,
                                                                           startThreadsCallable);
            actionCommand->execute(startThreadsCallable, sendCallable, protocolo);
        }
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
    clientReceiverThread->join();
    clientSenderThread->join();
    delete clientReceiverThread;
    delete clientSenderThread;
    closed = true;
}

void ClientManager::startClientThreads(ProtectedQueue<std::shared_ptr<ServerAction>> *qReceiver, BlockingQueue<std::shared_ptr<ServerUpdate>> *senderQueue) {
    //qReceiver -> ServerAction
    //senderQueue -> ServerUpdate
    this->shouldContinueLooping = false;
    clientReceiverThread = new ClientReceiver(client, qReceiver, id);
    clientSenderThread = new ClientSender(client, senderQueue, id);
    std::cout << "Starting client threads" << std::endl;
    clientReceiverThread->start();
    clientSenderThread->start();
}

bool ClientManager::joinThread() {
    return false;
}
bool ClientManager::endManager() {
    client.shutdown(2);
    client.close();
    clientReceiverThread->stop();
    clientSenderThread->stop();
    return closed;
}

uint8_t ClientManager::getId() {
    return id;
}

bool ClientManager::isClosed() {
    return closed;
}

void ClientManager::stop() {
    endManager();
}

ClientManager::~ClientManager() {}

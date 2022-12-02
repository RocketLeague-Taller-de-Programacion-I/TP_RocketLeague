//
// Created by lucaswaisten on 07/11/22.
//


#include "ClientManager.h"

ClientManager::ClientManager(uint8_t &id, Socket &aClient, GameManager &aGameManager) :
        client(std::move(aClient)),
        gameManager(aGameManager),
        closed(false),
        id(id){}

void ClientManager::run() {
    auto initialActionsQueue = new ProtectedQueue<std::shared_ptr<ServerAction>>;
    auto initialUpdatesQueue = new BlockingQueue<std::shared_ptr<ServerUpdate>>;

    startClientThreads(initialActionsQueue, initialUpdatesQueue);

    std::shared_ptr<ServerAction> command;

    std::function<BlockingQueue<std::shared_ptr<ServerUpdate>>*(ProtectedQueue<std::shared_ptr<ServerAction>>*)> queue_setter_callable =
            std::bind(&ClientManager::setQueues, this, std::placeholders::_1);

    bool playing = false; //  Mientras no se una o no cree una partida == no este jugando
    while (!playing) {
        try {
            command = initialActionsQueue->pop();
        } catch (...) {
            continue;
        }
        auto update = command->execute(this->gameManager, queue_setter_callable);
        //create,join y list
        if (update->getType()!= LIST_INFO and update->getReturnCode() == OK ) {
            if (update->getType() == JOIN_ACK) { break; }
            playing = true;
            std::cout<<"playing"<<std::endl;
        }
        initialUpdatesQueue->push(update);
    }

    waitClientThreads();
}

void ClientManager::waitClientThreads() {
    clientReceiverThread->join();
    clientSenderThread->join();
    delete clientReceiverThread;
    delete clientSenderThread;
    closed = true;
}

bool ClientManager::joinThread() {
    if (not closed) return false;
    return endManager();
}

bool ClientManager::endManager() {
    client.shutdown(2);
    client.close();
    clientReceiverThread->stop();
    clientSenderThread->stop();
    return closed;
}
void ClientManager::startClientThreads(ProtectedQueue<std::shared_ptr<ServerAction>> *qReceiver, BlockingQueue<std::shared_ptr<ServerUpdate>> *senderQueue) {
    //qReceiver -> ServerAction
    //senderQueue -> ServerUpdate
    clientReceiverThread = new ClientReceiver(client, qReceiver, id);
    clientSenderThread = new ClientSender(client, senderQueue, id);
    std::cout << "Starting client threads" << std::endl;
    clientReceiverThread->start();
    clientSenderThread->start();
}

BlockingQueue<std::shared_ptr<ServerUpdate>> * ClientManager::setQueues(
        ProtectedQueue<std::shared_ptr<ServerAction>> *gameQueue) {
    clientReceiverThread->swapQueue(gameQueue);
    return (clientSenderThread->getQueue());
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

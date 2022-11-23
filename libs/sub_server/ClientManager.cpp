//
// Created by lucaswaisten on 07/11/22.
//

#include <sys/socket.h>
#include <iostream>
#include <memory>
#include <functional>
#include "ClientManager.h"
#include "protocolo.h"
#include "ClientReceiver.h"

ClientManager::ClientManager(Socket &aClient,
                             GameManager &aGameManager) :
        client(std::move(aClient)),
        gameManager(aGameManager),
        closed(false){}

void ClientManager::run() {
    auto initialActionsQueue = new ProtectedQueue<Action*>;
    auto initialUpdatesQueue = new BlockingQueue<Action*>;

    startClientThreads(initialActionsQueue, initialUpdatesQueue);

    Action* command;

    std::function<BlockingQueue<Action*>*(ProtectedQueue<Action *> *)> queue_setter_callable =
            std::bind(&ClientManager::setQueues, this, std::placeholders::_1);

    bool playing = false; //  Mientras no se una o no cree una partida == no este jugando
    while (!playing) {
        try {
            command = initialActionsQueue->pop();
        } catch (...) {
            continue;
        }
        auto action = command->execute(this->gameManager, queue_setter_callable);
        if (action->getReturnMessage() == "OK") {
            playing = true;
            std::cout<<"playing"<<std::endl;
        }
        initialUpdatesQueue->push(action);
    }
}

bool ClientManager::joinThread() {
    if (not closed) return false;
    return this->endManager();
}

bool ClientManager::endManager() {
    closed = true;
    client.shutdown(2);
    client.close();
    this->clientReceiverThread->join();
    this->clientSenderThread->join();
    delete this->clientReceiverThread;
    delete this->clientSenderThread;
    this->join();
    return closed;
}

void ClientManager::attendClient(unsigned long aId) {
    this->id = aId;
    this->start();
}

void ClientManager::startClientThreads(ProtectedQueue<Action *> *qReceiver, BlockingQueue<Action *> *senderQueue) {
    clientReceiverThread = new ClientReceiver(client, qReceiver, id);
    clientSenderThread = new ClientSender(client, senderQueue, id);
    std::cout << "Starting client threads" << std::endl;
    clientReceiverThread->start();
    clientSenderThread->start();
}
BlockingQueue<Action*>* ClientManager::setQueues(ProtectedQueue<Action *> *gameQueue) {
    clientReceiverThread->setQueue(gameQueue);
    return (clientSenderThread->getQueue());
}

void ClientManager::stop() {}

ClientManager::~ClientManager() {
    endManager();
}
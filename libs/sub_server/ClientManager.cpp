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
        closed(false), id(0){}

void ClientManager::run() {
    auto initialActionsQueue = new ProtectedQueue<Action*>;
    auto initialUpdatesQueue = new BlockingQueue <Action*>;

    startClientThreads(initialActionsQueue, initialUpdatesQueue);

    Action* command;

    std::function<BlockingQueue<Action*>*(ProtectedQueue<Action *>*)> queue_setter_callable =
            std::bind(&ClientManager::setQueues, this, std::placeholders::_1);

    bool playing = false; //  Mientras no se una o no cree una partida == no este jugando
    while (!playing) {
        try {
            if (initialActionsQueue->isEmpty()) { continue; }
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
    /*
    std::vector<uint8_t> data;
    data.push_back(this->id);
    uint8_t byte_to_read;
    Protocolo protocolo;
    this->client.recvall(&byte_to_read, sizeof(byte_to_read), &closed);
    while (byte_to_read != NOP && !closed) {
        data.push_back(byte_to_read);
        this->client.recvall(&byte_to_read, sizeof(byte_to_read), &closed);
    }

    // form the Action from the data
    auto action = protocolo.deserializeData(data);


//    action->execute(gameManager,startClientThreads);
    uint8_t idCreator = id,capacity;
    std::string nameGame = action->getGameName();

    if (action->getType() == CREATE_ROOM) {
        capacity = action->getCapacity();
    } else if (action->getType() == LIST_ROOMS) {
        capacity = 0;
    }
    std::string result = gameManager.executeAction(action->getType(), idCreator, capacity, nameGame, queue_setter_callable);
    if (action->getType() == LIST_ROOMS) {
        //we need to send the data without creating nor joining a game
        if (not closed) {
            std::vector<uint8_t> listData;
            listData.push_back(LIST_ROOMS);
            listData.push_back(id);
            // listData.insert(listData.end(), result.begin(), result.end());
            //  se iteran los comandos parseados y se envian al servidor
            for (uint8_t c : listData) {
                client.sendall(&c, sizeof(c), &closed);
            }
            //  send the NOP instruccion
            client.sendall(result.c_str(), result.size(), &closed);
            uint8_t nop = 0;
            client.sendall(&nop, sizeof(nop), &closed);
        }
        // we need to receive the join action
        data.clear();
        this->client.recvall(&byte_to_read, sizeof(byte_to_read), &closed);
        while (byte_to_read != NOP && !closed) {
            data.push_back(byte_to_read);
            this->client.recvall(&byte_to_read, sizeof(byte_to_read), &closed);
        }

        auto joinaction = protocolo.deserializeData(data);
        std::string gameName = joinaction->getGameName();
        gameManager.executeAction(joinaction->getType(), idCreator, capacity, gameName, queue_setter_callable);
    }
    */
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
    clientReceiverThread = new ClientReceiver(client, qReceiver);
    clientSenderThread = new ClientSender(client, senderQueue);
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
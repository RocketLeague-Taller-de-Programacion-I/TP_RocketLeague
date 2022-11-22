//
// Created by lucaswaisten on 07/11/22.
//

#include <sys/socket.h>
#include <iostream>
#include <memory>
#include <functional>
#include "ClientManager.h"
#include "ActionMaker.h"

ClientManager::ClientManager(Socket &aClient,
                             GameManager &aGameManager) :
                             client(std::move(aClient)),
                             gameManager(aGameManager),
                             closed(false), id(0){}

void ClientManager::run() {
    std::vector<uint8_t> data;
    uint8_t byte_to_read;
    ActionMaker maker;
    this->client.recvall(&byte_to_read, sizeof(byte_to_read), &closed);
    while (byte_to_read != NOP && !closed) {
        data.push_back(byte_to_read);
        this->client.recvall(&byte_to_read, sizeof(byte_to_read), &closed);
    }

    // create a callback function to start the client threads
    std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> queue_setter_callable =
            [this](BlockingQueue<Action*> *qr,BlockingQueue<Action*> *qs){return this->startClientThreads(qr,qs);};

    // form the Action from the data
    auto action = maker.makeAction(data, gameManager, queue_setter_callable);

    exectue(action);
}

bool ClientManager::joinThread() {
    if (not closed) return false;
    return this->endManager();
}

bool ClientManager::endManager() {
    closed = true;
    client.shutdown(SHUT_RDWR);
    client.close();
    this->join();
    return closed;
}

void ClientManager::attendClient(unsigned long aId) {
    this->id = aId;
    this->start();
}

void ClientManager::startClientThreads(BlockingQueue<Action *> *qReceiver, BlockingQueue<Action *> *senderQueue) {
    clientReceiverThread = new ClientReceiver(client, *qReceiver);
    clientSenderThread = new ClientSender(client, *senderQueue);
    std::cout << "Starting client threads" << std::endl;
    clientReceiverThread->start();
    clientSenderThread->start();
}

void ClientManager::stop() {}

void ClientManager::exectue(Action *pAction) {

}

void ClientManager::exectue(ActionCreateServer *pAction) {
    pAction->execute();
}

void ClientManager::exectue(ActionJoinServer *pAction) {
    pAction->execute();
}

void ClientManager::exectue(ActionListServer *pAction) {
    std::vector<uint8_t> data;
    uint8_t byte_to_read;
    ActionMaker maker;

    std::string result(gameManager.listGames());

    //we need to send the data without creating nor joining a game
    if (not closed) {
        std::vector<uint8_t> listData;
        listData.push_back(UPDATE);
        listData.push_back(id);
        listData.insert(listData.end(), result.begin(), result.end());
        //  se iteran los comandos parseados y se envian al servidor
        for (uint8_t c : listData) {
            client.sendall(&c, sizeof(c), &closed);
        }
        //  send the NOP instruccion
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
    std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> queue_setter_callable =
            [this](BlockingQueue<Action*> *qr,BlockingQueue<Action*> *qs){return this->startClientThreads(qr,qs);};

    auto joinaction = maker.makeAction(data, gameManager, queue_setter_callable);
    joinaction->execute();
}

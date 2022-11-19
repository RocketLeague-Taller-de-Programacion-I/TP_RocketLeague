//
// Created by lucaswaisten on 07/11/22.
//
#pragma once

#include <sys/socket.h>
#include <iostream>
#include <memory>
#include <functional>
#include "ClientManager.h"
#include "sub_common/protocolo.h"

ClientManager::ClientManager(Socket &aClient,
                             GameManager &aGameManager) :
                             client(std::move(aClient)),
                             gameManager(aGameManager),
                             closed(false), id(0){}

void ClientManager::run() {
    std::vector<uint8_t> data(id);
    uint8_t byte_to_read;
    Protocolo protocolo;

    do {
        data.push_back(byte_to_read);
        this->client.recvall(&byte_to_read, sizeof(byte_to_read), &closed);
    } while (byte_to_read != NOP && !closed) ;

    // form the Action from the data
    auto action = protocolo.deserializarData(data);
    // callback
    auto queue_setter_callable = std::bind(std::mem_fn(&ClientManager::setQueueReceiver),
                                           this, std::placeholders::_1);

    action->execute(gameManager,queue_setter_callable);
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

void ClientManager::setQueueReceiver(BlockingQueue<Action> *qReceiver) {}

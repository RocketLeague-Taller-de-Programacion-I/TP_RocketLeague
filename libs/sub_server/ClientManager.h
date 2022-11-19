//
// Created by lucaswaisten on 07/11/22.
//
#pragma once

#ifndef ROCKETLEAGUE_CLIENTMANAGER_H
#define ROCKETLEAGUE_CLIENTMANAGER_H

#include "../sub_common/thread.h"
#include "../sub_common/socket.h"
#include "sub_common/BlockingQueue.h"
#include "gameManager.h"

class ClientManager : public Thread{
private:
    Socket client;
    GameManager &gameManager;
    bool closed;
    uint8_t id;
public:
    ClientManager(Socket &aClient, GameManager &aGameManager);

    void run() override;

    bool joinThread();

    bool endManager();

    void attendClient(unsigned long aId);

    void setQueueReceiver(BlockingQueue<Action> *qReceiver);
};


#endif //ROCKETLEAGUE_CLIENTMANAGER_H

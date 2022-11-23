//
// Created by lucaswaisten on 07/11/22.
//
#pragma once

#ifndef ROCKETLEAGUE_CLIENTMANAGER_H
#define ROCKETLEAGUE_CLIENTMANAGER_H

#include "gameManager.h"
#include "../sub_common/thread.h"
#include "../sub_common/socket.h"
#include "protocolo.h"
#include "sub_common/BlockingQueue.h"
#include "ClientReceiver.h"
#include "ClientSender.h"

class ClientManager : public Thread{
private:
    Socket client;
    GameManager &gameManager;
    bool closed;
    uint8_t id;
    ClientReceiver *clientReceiverThread;
    ClientSender *clientSenderThread;
public:

    ClientManager(Socket &aClient, GameManager &aGameManager);
    ~ClientManager() override;
    void run() override;
    void stop() override;

    bool joinThread();

    bool endManager();

    void attendClient(unsigned long aId);

    void startClientThreads(BlockingQueue<Action *> *qReceiver, BlockingQueue<Action *> *senderQueue);

    BlockingQueue<Action *>* setQueues(BlockingQueue<Action *> *gameQueue);
};


#endif //ROCKETLEAGUE_CLIENTMANAGER_H
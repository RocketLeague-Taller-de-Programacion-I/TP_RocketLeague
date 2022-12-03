#pragma once

#ifndef ROCKETLEAGUE_CLIENTMANAGER_H
#define ROCKETLEAGUE_CLIENTMANAGER_H

#include <iostream>
#include <memory>
#include <functional>
#include <atomic>

#include "gameManager.h"
#include "../sub_common/thread.h"
#include "../sub_common/socket.h"
#include "ServerProtocolo.h"
#include "sub_common/BlockingQueue.h"
#include "ClientReceiver.h"
#include "ClientSender.h"

class ClientManager : public Thread{
private:
    Socket client;
    GameManager &gameManager;
    bool closed;
    uint8_t id;
    std::atomic<bool> shouldContinueLooping;
    ClientReceiver *clientReceiverThread;
    ClientSender *clientSenderThread;

public:
    ClientManager(uint8_t &id, Socket &aClient, GameManager &aGameManager);
    ~ClientManager() override;
    void run() override;

    void stop() override;

    bool joinThread();

    bool endManager();

    void startClientThreads(ProtectedQueue<std::shared_ptr<ServerAction>> *qReceiver, BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>> *senderQueue);

    void waitClientThreads();

    uint8_t getId();

    void receiveBytes(void *bytes_to_receive, int sizeToReceive);

    void sendBytes(void *bytes_to_send, unsigned int size);
};


#endif //ROCKETLEAGUE_CLIENTMANAGER_H
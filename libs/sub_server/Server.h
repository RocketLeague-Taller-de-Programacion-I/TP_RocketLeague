//
// Created by franco on 24/10/22.
//

#ifndef ROCKETLEAGUE_SERVER_H
#define ROCKETLEAGUE_SERVER_H


#include <vector>
#include "../sub_common/thread.h"
#include "../sub_common/socket.h"
#include "gameManager.h"
#include "ClientReceiver.h"
#include "ClientSender.h"
#include "sub_common/BlockingQueue.h"
#include "sub_common/Action.h"
#include "sub_common/Update.h"

class Server : public Thread{
 private:
    bool closed;
    Socket accept_skt;
    std::vector<ClientSender*> senders;
    std::vector<ClientReceiver*> recivers;

    BlockingQueue<Action> receiverQueue;
    BlockingQueue<Update> senderQueue;

 public:
    explicit Server(const std::string& servname);

    ~Server() override;

    void run() override;

    void stop();

    void garbageCollector();

    void cleanManagers();
};


#endif //ROCKETLEAGUE_SERVER_H

//
// Created by franco on 24/10/22.
//

#ifndef ROCKETLEAGUE_SERVER_H
#define ROCKETLEAGUE_SERVER_H


#include <vector>
#include "../sub_common/thread.h"
#include "../sub_common/socket.h"
#include "gameManager.h"

class Server : public Thread{
 private:
    bool closed;
    Socket accept_skt;
    //std::vector<ClientSender*> senders;
    //std::vector<ClientReceiver*> receivers;
    std::vector<ClientManager*> managers;
 public:
    explicit Server(const std::string& servname);

    ~Server() override;

    void run() override;

    void stop();

    void garbageCollector();

    void cleanManagers();

};


#endif //ROCKETLEAGUE_SERVER_H

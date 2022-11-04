//
// Created by franco on 24/10/22.
//

#ifndef ROCKETLEAGUE_SERVER_H
#define ROCKETLEAGUE_SERVER_H


#include "../sub_common/thread.h"
#include "../sub_common/socket.h"
#include "gameManager.h"
#include "clientManager.h"

class Server : public Thread{
 private:
    bool cerrado;
    Socket acept_skt;
 public:
    explicit Server(const std::string& servname);

    ~Server() override;

    void run() override;

    void stop() override;

};


#endif //ROCKETLEAGUE_SERVER_H

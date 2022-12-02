//
// Created by franco on 24/10/22.
//
#pragma once

#ifndef ROCKETLEAGUE_SERVER_H
#define ROCKETLEAGUE_SERVER_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <sys/socket.h>
#include <atomic>

#include "../sub_common/socket.h"
#include "ClientManager.h"

class Server : public Thread {
private:
    std::atomic<bool> closed;
    Socket accept_skt;
    std::vector<ClientManager*> managers;
protected:
    void run() override;
public:
    explicit Server(const char *port);
    void stop() override;

    void garbageCollector();
    void cleanManagers();
};


#endif //ROCKETLEAGUE_SERVER_H
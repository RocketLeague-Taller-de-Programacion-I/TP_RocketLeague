//
// Created by franco on 24/10/22.
//

#ifndef ROCKETLEAGUE_SERVER_H
#define ROCKETLEAGUE_SERVER_H

#include <cmath>
#include <iostream>
#include <iostream>
#include <algorithm>
#include <sys/socket.h>
#include <vector>

#include "RenderThread.h"
#include "sub_common/socket.h"
#include "sub_common/ClientSender.h"
#include "sub_common/ClientReceiver.h"

class Client : public Thread {
private:
    Socket skt_client;
    bool closed;
    std::vector<Thread*> threads;
protected:
    void run() override;
public:
    Client(const char *host, const char *port);
    ~Client();
    void stop() override;
    void cleanThreads();

    void startThreads();

    void garbageCollector();
};


#endif //ROCKETLEAGUE_SERVER_H

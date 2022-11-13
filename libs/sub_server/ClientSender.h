//
// Created by lucaswaisten on 12/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTSENDER_H
#define ROCKETLEAGUE_CLIENTSENDER_H


#include "sub_common/socket.h"
#include "sub_common/thread.h"
#include "sub_common/MonitorSocket.h"

class ClientSender : public Thread{
private:
    bool closed;
public:
    explicit ClientSender(MonitorSocket &aMonitor);
    void run();


    bool joinThread();
};


#endif //ROCKETLEAGUE_CLIENTSENDER_H

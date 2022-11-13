//
// Created by lucaswaisten on 12/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTRECEIVER_H
#define ROCKETLEAGUE_CLIENTRECEIVER_H


#include "sub_common/socket.h"
#include "sub_common/thread.h"
#include "sub_common/MonitorSocket.h"

class ClientReceiver : public Thread{

public:
    explicit ClientReceiver(MonitorSocket& aMonitor);
    void run();

    bool joinThread();
};


#endif //ROCKETLEAGUE_CLIENTRECEIVER_H

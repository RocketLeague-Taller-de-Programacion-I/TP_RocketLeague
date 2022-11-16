//
// Created by lucaswaisten on 12/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTRECEIVER_H
#define ROCKETLEAGUE_CLIENTRECEIVER_H


#include "sub_common/socket.h"
#include "sub_common/thread.h"

class ClientReceiver : public Thread{
private:
    Socket &skt_client;
public:
    explicit ClientReceiver(Socket &skt_client);
    void run();

    bool joinThread();
};


#endif //ROCKETLEAGUE_CLIENTRECEIVER_H

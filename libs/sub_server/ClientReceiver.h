//
// Created by lucaswaisten on 12/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTRECEIVER_H
#define ROCKETLEAGUE_CLIENTRECEIVER_H


#include "sub_common/socket.h"
#include "sub_common/thread.h"
#include "protocolo.h"
#include "sub_common/ProtectedQueue.h"

#include "server_actions/ServerAction.h"

class ClientReceiver : public Thread{
private:
    Socket &skt_client;
    bool closed;
    uint8_t idClient;
protected:
    void run() override;
public:
    ProtectedQueue<ServerAction*> *updatesQueue;
    ClientReceiver(Socket &skt_client, ProtectedQueue<ServerAction *> *updatesQueue, uint8_t idClient);
    ~ClientReceiver() override;
    void stop() override;
    void setQueue(ProtectedQueue<ServerAction *> *pQueue);
    void clearQueue();
};


#endif //ROCKETLEAGUE_CLIENTRECEIVER_H

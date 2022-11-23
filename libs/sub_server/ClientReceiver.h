//
// Created by lucaswaisten on 12/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTRECEIVER_H
#define ROCKETLEAGUE_CLIENTRECEIVER_H


#include "sub_common/socket.h"
#include "sub_common/thread.h"
#include "sub_server/Action.h"
#include "protocolo.h"
#include "sub_common/BlockingQueue.h"
#include "sub_common/ProtectedQueue.h"

class ClientReceiver : public Thread{
private:
    Socket &skt_client;
    bool closed;
protected:
    void run() override;
public:
    BlockingQueue<Action*> *updatesQueue;
    ClientReceiver(Socket &skt_client, BlockingQueue<Action *> *updatesQueue);
    ~ClientReceiver() override;
    void stop() override;
    void setQueue(BlockingQueue<Action *> *pQueue);
    void clearQueue();
};


#endif //ROCKETLEAGUE_CLIENTRECEIVER_H

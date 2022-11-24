//
// Created by roby on 22/11/22.
//

#ifndef ROCKETLEAGUE_THREADACTIONSSENDER_H
#define ROCKETLEAGUE_THREADACTIONSSENDER_H


#include "sub_common/socket.h"
#include "sub_common/thread.h"
#include "../sub_common/BlockingQueue.h"
#include "sub_client/client_actions/ClientAction.h"

class ThreadActionsSender : public Thread{
private:
    Socket &skt_client;
    bool closed;
protected:
    void run() override;
public:
    BlockingQueue<ClientAction*> &actionsQueue;

    explicit ThreadActionsSender(Socket &skt_client, BlockingQueue <ClientAction*> &actionsQueue);
    ~ThreadActionsSender() override;
    void stop() override;
};


#endif //ROCKETLEAGUE_THREADACTIONSSENDER_H

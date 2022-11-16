//
// Created by lucaswaisten on 12/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTSENDER_H
#define ROCKETLEAGUE_CLIENTSENDER_H


#include "sub_common/socket.h"
#include "sub_common/thread.h"
#include "Action.h"
#include "protocolo.h"
#include "BlockingQueue.h"

class ClientSender : public Thread{
private:
    Socket &skt_client;
    bool closed;
protected:
    void run() override;
public:
    BlockingQueue<Action> &actionsQueue;

    explicit ClientSender(Socket &skt_client, BlockingQueue <Action> &actionsQueue);

    void stop() override;
    bool joinThread();
};


#endif //ROCKETLEAGUE_CLIENTSENDER_H

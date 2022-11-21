//
// Created by lucaswaisten on 12/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTRECEIVER_H
#define ROCKETLEAGUE_CLIENTRECEIVER_H


#include "sub_common/socket.h"
#include "sub_common/thread.h"
#include "sub_common/sub_action/Action.h"
#include "protocolo.h"
#include "BlockingQueue.h"

class ClientReceiver : public Thread{
private:
    Socket &skt_client;
    bool closed;
protected:
    void run() override;
public:
    BlockingQueue<Action*> &updatesQueue;

    explicit ClientReceiver(Socket &skt_client, BlockingQueue<Action *> &updatesQueue);

    void stop() override;
};


#endif //ROCKETLEAGUE_CLIENTRECEIVER_H

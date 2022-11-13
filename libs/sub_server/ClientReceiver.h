//
// Created by lucaswaisten on 12/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTRECEIVER_H
#define ROCKETLEAGUE_CLIENTRECEIVER_H


#include "sub_common/socket.h"
#include "sub_common/thread.h"
#include "sub_common/MonitorSocket.h"
#include "sub_common/BlockingQueue.h"
#include "sub_common/Action.h"

class ClientReceiver : public Thread{
private:
    bool closed;
    Socket &socket;
    BlockingQueue<Action> &queueAction;
public:
    explicit ClientReceiver(Socket &aSkt, BlockingQueue <Action> &queue);
    void run() override;

    bool joinThread();



};


#endif //ROCKETLEAGUE_CLIENTRECEIVER_H

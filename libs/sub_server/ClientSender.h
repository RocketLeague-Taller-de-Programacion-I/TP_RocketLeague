//
// Created by lucaswaisten on 12/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTSENDER_H
#define ROCKETLEAGUE_CLIENTSENDER_H


#include "sub_common/socket.h"
#include "sub_common/thread.h"
#include "sub_common/MonitorSocket.h"
#include "sub_common/BlockingQueue.h"
#include "sub_common/Update.h"

class ClientSender : public Thread{
private:
    bool closed;
    Socket &socket;
    BlockingQueue<Update> &queueUpdates;
public:
    explicit ClientSender(Socket &aSkt, BlockingQueue <Update> &queue);
    void run() override;


    bool joinThread();


};


#endif //ROCKETLEAGUE_CLIENTSENDER_H

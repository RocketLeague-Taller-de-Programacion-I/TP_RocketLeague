//
// Created by roby on 22/11/22.
//

#ifndef ROCKETLEAGUE_UPDATESRECEIVERTHREAD_H
#define ROCKETLEAGUE_UPDATESRECEIVERTHREAD_H

#include <vector>

#include "sub_common/socket.h"
#include "sub_common/thread.h"
#include "../sub_common/ProtectedQueue.h"

#include "ClientProtocol.h"
#include "GameUpdate.h"

class UpdatesReceiverThread : public Thread{
private:
    Socket &skt_client;
    bool closed;
protected:
    void run() override;
public:
    BlockingQueue<GameUpdate*> &updatesQueue;
    explicit UpdatesReceiverThread(Socket &skt_client, ProtectedQueue<GameUpdate*> &updatesQueue);

    void stop() override;
};


#endif //ROCKETLEAGUE_UPDATESRECEIVERTHREAD_H

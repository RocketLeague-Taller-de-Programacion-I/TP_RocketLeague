//
// Created by roby on 22/11/22.
//

#ifndef ROCKETLEAGUE_UPDATESRECEIVERTHREAD_H
#define ROCKETLEAGUE_UPDATESRECEIVERTHREAD_H

#include <vector>
#include <atomic>
#include <netinet/in.h>

#include "sub_common/socket.h"
#include "sub_common/thread.h"
#include "../sub_common/BlockingQueue.h"
#include "../sub_common/ProtectedQueue.h"

#include "ClientProtocol.h"
#include "sub_client/client_updates/ClientUpdate.h"

class UpdatesReceiverThread : public Thread{
private:
    Socket &skt_client;
    bool closed;
    std::atomic<bool> finished;
protected:
    void run() override;
public:
    ProtectedQueue<std::shared_ptr<ClientUpdate>> &updatesQueue;

    explicit UpdatesReceiverThread(Socket &skt_client, ProtectedQueue<std::shared_ptr<ClientUpdate>> &updatesQueue);
    UpdatesReceiverThread();
    ~UpdatesReceiverThread() override = default;

    void receiveBytes(void *bytes_to_read, int size);

    void stop() override;
};


#endif //ROCKETLEAGUE_UPDATESRECEIVERTHREAD_H

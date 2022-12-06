//
// Created by roby on 22/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONSSENDERTHREAD_H
#define ROCKETLEAGUE_ACTIONSSENDERTHREAD_H


#include "sub_common/socket.h"
#include "sub_common/thread.h"
#include "../sub_common/BlockingQueue.h"
#include "sub_client/client_actions/ClientAction.h"
#include "ClientProtocol.h"
#include <optional>

class ActionsSenderThread : public Thread{
private:
    Socket &skt_client;
    bool closed;
protected:
    void run() override;
public:
    BlockingQueue<std::optional<std::shared_ptr<ClientAction>>> &actionsQueue;

    explicit ActionsSenderThread(Socket &skt_client, BlockingQueue<std::optional<std::shared_ptr<ClientAction>>> &actionsQueue);
    ActionsSenderThread();

    ~ActionsSenderThread() override;
    void stop() override;

    void sendBytes(void *bytes_to_send, int i);
};


#endif //ROCKETLEAGUE_ACTIONSSENDERTHREAD_H

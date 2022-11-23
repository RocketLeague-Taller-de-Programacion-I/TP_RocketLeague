//
// Created by lucaswaisten on 12/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTSENDER_H
#define ROCKETLEAGUE_CLIENTSENDER_H


#include "sub_common/socket.h"
#include "sub_common/thread.h"
#include "sub_server/Action.h"
#include "protocolo.h"
#include "sub_common/BlockingQueue.h"

class ClientSender : public Thread{
private:
    Socket &skt_client;
    bool closed;
    uint8_t idClient;
protected:
    void run() override;
public:
    BlockingQueue<Action*> *actionsQueue;

    explicit ClientSender(Socket &skt_client, BlockingQueue<Action *> *queue, uint8_t idClient);
    ~ClientSender() override;
    void stop() override;
    BlockingQueue<Action *>* getQueue() const;
};


#endif //ROCKETLEAGUE_CLIENTSENDER_H

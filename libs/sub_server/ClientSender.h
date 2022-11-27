//
// Created by lucaswaisten on 12/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTSENDER_H
#define ROCKETLEAGUE_CLIENTSENDER_H


#include "sub_common/socket.h"
#include "sub_common/thread.h"
#include "ServerProtocolo.h"
#include "sub_common/BlockingQueue.h"

#include "server_updates/ServerUpdate.h"
//WorldUpdate

class ClientSender : public Thread{
private:
    Socket &skt_client;
    bool closed;
    uint8_t idClient;
protected:
    void run() override;
public:
    BlockingQueue<ServerUpdate*> *actionsQueue;

    explicit ClientSender(Socket &skt_client, BlockingQueue<ServerUpdate *> *queue, uint8_t idClient);
    ~ClientSender() override;
    void stop() override;
    BlockingQueue<ServerUpdate *> * getQueue() const;
};


#endif //ROCKETLEAGUE_CLIENTSENDER_H

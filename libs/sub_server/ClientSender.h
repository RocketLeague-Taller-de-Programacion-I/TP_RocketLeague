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
    BlockingQueue<std::shared_ptr<ServerUpdate>> *actionsQueue;

    explicit ClientSender(Socket &skt_client, BlockingQueue<std::shared_ptr<ServerUpdate>> *queue, uint8_t idClient);
    ~ClientSender() override;
    void stop() override;
    BlockingQueue<std::shared_ptr<ServerUpdate>> * getQueue() const;

    void sendBytes(void *bytes_to_send, unsigned int size);
};


#endif //ROCKETLEAGUE_CLIENTSENDER_H

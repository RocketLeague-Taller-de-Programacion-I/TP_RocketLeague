//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_SERVERCREATEROOM_H
#define ROCKETLEAGUE_SERVERCREATEROOM_H


#include "ServerAction.h"
#include "sub_server/server_updates/ServerCreateACK.h"

class ServerCreateRoom : public ServerAction {
private:
    uint8_t capacity;
public:
    ServerCreateRoom(const uint8_t &id, uint8_t &capacity, std::string &data);
    ~ServerCreateRoom() override = default;

    uint8_t getCapacity() { return capacity; }

    ServerUpdate * execute(GameManager &manager, const std::function<BlockingQueue<ServerUpdate *> *(
            ProtectedQueue<ServerAction *> *)> &setQueue) override;
    void execute(Match &match) override {};
};


#endif //ROCKETLEAGUE_SERVERCREATEROOM_H

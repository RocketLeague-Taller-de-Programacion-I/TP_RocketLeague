//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_SERVERJOINROOM_H
#define ROCKETLEAGUE_SERVERJOINROOM_H

#include "ServerAction.h"
#include "sub_server/server_updates/ServerJoinACK.h"

class ServerJoinRoom : public ServerAction {

public:
    ServerJoinRoom(const uint8_t &id, std::string &data);
    ~ServerJoinRoom() override = default;

    virtual ServerUpdate * execute(GameManager &manager, const std::function<BlockingQueue<ServerUpdate *> *(
            ProtectedQueue<ServerAction *> *)> &setQueue) override;
};


#endif //ROCKETLEAGUE_SERVERJOINROOM_H

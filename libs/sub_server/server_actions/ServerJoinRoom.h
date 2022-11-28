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
    void execute(Match& match) override;
    virtual std::shared_ptr<ServerUpdate> execute(GameManager &manager, const std::function<BlockingQueue<std::shared_ptr<ServerUpdate>> *(
            ProtectedQueue<std::shared_ptr<ServerAction>> *)> &setQueue) override;
};


#endif //ROCKETLEAGUE_SERVERJOINROOM_H

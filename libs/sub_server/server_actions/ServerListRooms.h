//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_SERVERLISTROOMS_H
#define ROCKETLEAGUE_SERVERLISTROOMS_H

#include "ServerAction.h"
#include "sub_server/server_updates/ServerListACK.h"

class ServerListRooms : public ServerAction {
public:
    explicit ServerListRooms(const uint8_t &id) : ServerAction(id) {};
    ~ServerListRooms() override = default;

    void execute(Match& match) override;
    virtual std::shared_ptr<ServerUpdate> execute(GameManager &manager, const std::function<BlockingQueue<std::shared_ptr<ServerUpdate>> *(
            ProtectedQueue<ServerAction *> *)> &setQueue) override;
};


#endif //ROCKETLEAGUE_SERVERLISTROOMS_H

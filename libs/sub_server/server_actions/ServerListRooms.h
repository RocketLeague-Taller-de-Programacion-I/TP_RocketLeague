//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_SERVERLISTROOMS_H
#define ROCKETLEAGUE_SERVERLISTROOMS_H

#include "ServerAction.h"
#include "sub_server/server_updates/ServerListACK.h"

class ServerListRooms : public ServerAction {
private:
    GameManager &manager;
public:
    explicit ServerListRooms(const uint8_t &id, GameManager &manager) : ServerAction(id), manager(manager) {};
    ~ServerListRooms() override = default;

    void execute(Match& match) override;
    void execute(std::function<void(ProtectedQueue<std::shared_ptr<ServerAction>> *,
                                    BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>> *)> &startThreadsCallable,
                 std::function<void(void *, unsigned int)> &sendCallable,
                 ServerProtocolo &protocolo) override;
};


#endif //ROCKETLEAGUE_SERVERLISTROOMS_H

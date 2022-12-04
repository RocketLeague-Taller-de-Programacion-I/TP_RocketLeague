//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_SERVERJOINROOM_H
#define ROCKETLEAGUE_SERVERJOINROOM_H

#include "ServerAction.h"
#include "sub_server/server_updates/ServerJoinACK.h"

class ServerJoinRoom : public ServerAction {
private:
    GameManager &manager;
public:
    ServerJoinRoom(const uint8_t &id, std::string &data, GameManager &manager) : ServerAction(id, data), manager(manager) {};
    ~ServerJoinRoom() override = default;
    void execute(Match& match) override;
    void execute(std::function<void(ProtectedQueue<std::shared_ptr<ServerAction>> *,
                                    BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>> *)> &startThreadsCallable,
                 std::function<void(void *, unsigned int)> &sendCallable,
                 ServerProtocolo &protocolo) override;
};


#endif //ROCKETLEAGUE_SERVERJOINROOM_H

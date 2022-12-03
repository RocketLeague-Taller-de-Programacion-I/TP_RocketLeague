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
    GameManager &manager;
public:
    ServerCreateRoom(const uint8_t &id, uint8_t &capacity, std::string &data, GameManager &manager) : ServerAction(id, data) , capacity(capacity), manager(manager) {};
    ~ServerCreateRoom() override = default;

    uint8_t getCapacity() { return capacity; }

    void execute(Match& match) override;

    void execute(std::function<void(ProtectedQueue<std::shared_ptr<ServerAction>> *,
                                    BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>> *)> &startThreadsCallable,
                 std::function<void(void *, unsigned int)> &sendCallable,
                 ServerProtocolo &protocolo) override;
};


#endif //ROCKETLEAGUE_SERVERCREATEROOM_H

//
// Created by roby on 27/11/22.
//

#ifndef ROCKETLEAGUE_SERVERACTIONMOVE_H
#define ROCKETLEAGUE_SERVERACTIONMOVE_H

#include "ServerAction.h"

class ServerActionMove : public ServerAction {
//[type, id, direction, state}
private:
    uint8_t direction;
    bool state;
public:
    ServerActionMove(const uint8_t &id, uint8_t &direction, bool &state);

    ~ServerActionMove() override = default;

    void execute(std::function<void(ProtectedQueue<std::shared_ptr<ServerAction>> *,
                                    BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>> *)> &startThreadsCallable,
                 std::function<void(void *, unsigned int)> &sendCallable,
                 ServerProtocolo &protocolo) override {};

    void execute(Match &match) override;
};

#endif //ROCKETLEAGUE_SERVERACTIONMOVE_H

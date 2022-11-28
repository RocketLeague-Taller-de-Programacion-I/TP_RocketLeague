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
    ServerActionMove(const uint8_t &id, uint8_t &direction, bool state) :
            ServerAction(id),
            direction(direction),
            state(state) {};

    ~ServerActionMove() override = default;

    ServerUpdate * execute(GameManager &manager, const std::function<BlockingQueue<ServerUpdate *> *(
            ProtectedQueue<ServerAction *> *)> &setQueue) override { return nullptr; };
    void execute(Match &match) override;
};

#endif //ROCKETLEAGUE_SERVERACTIONMOVE_H

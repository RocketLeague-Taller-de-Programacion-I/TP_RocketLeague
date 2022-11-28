//
// Created by roby on 27/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTACTIONMOVE_H
#define ROCKETLEAGUE_CLIENTACTIONMOVE_H

#include "ClientAction.h"

class ClientActionMove : public ClientAction{
private:
    uint8_t direction;
    bool state;
public:
    ClientActionMove(uint8_t &direction, bool state);
    ~ClientActionMove() override = default;

    std::vector<uint8_t> beSerialized() override;
    uint8_t getType() const override { return MOVE; };
};


#endif //ROCKETLEAGUE_CLIENTACTIONMOVE_H

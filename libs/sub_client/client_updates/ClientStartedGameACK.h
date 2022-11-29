//
// Created by roby on 27/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTSTARTEDGAMEACK_H
#define ROCKETLEAGUE_CLIENTSTARTEDGAMEACK_H

#include "ClientUpdate.h"

class ClientStartedGameACK : public ClientUpdate {
 public:
    ClientStartedGameACK(uint8_t &id, uint8_t &returnCode) : ClientUpdate(id, returnCode){}
    ~ClientStartedGameACK() = default;

    uint8_t getType() const override { return STARTED_GAME_ACK; };
};


#endif //ROCKETLEAGUE_CLIENTSTARTEDGAMEACK_H

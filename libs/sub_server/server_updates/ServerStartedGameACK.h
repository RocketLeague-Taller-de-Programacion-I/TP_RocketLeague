//
// Created by roby on 27/11/22.
//

#ifndef ROCKETLEAGUE_SERVERSTARTEDGAMEACK_H
#define ROCKETLEAGUE_SERVERSTARTEDGAMEACK_H

#include "ServerUpdate.h"

class ServerStartedGameACK : public ServerUpdate{
public:
    ServerStartedGameACK(const uint16_t &id, uint16_t &returnCode) : ServerUpdate(id, returnCode){}
    ~ServerStartedGameACK() override = default;

    uint16_t getType() const override;
    std::vector<uint16_t> beSerialized() override;
};


#endif //ROCKETLEAGUE_SERVERSTARTEDGAMEACK_H

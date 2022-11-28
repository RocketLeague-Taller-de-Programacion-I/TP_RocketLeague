//
// Created by roby on 25/11/22.
//

#ifndef ROCKETLEAGUE_SERVERUPDATEWORLD_H
#define ROCKETLEAGUE_SERVERUPDATEWORLD_H

#include "ServerUpdate.h"

class ServerUpdateWorld : public ServerUpdate{
private:
    std::vector<int> info;
public:
    ServerUpdateWorld(uint8_t &id, uint8_t &returnCode, std::vector<int> &info) : ServerUpdate(id, returnCode), info(info) {};
    ~ServerUpdateWorld() override = default;

    uint8_t getType() const override;
    std::vector<uint8_t> beSerialized() override;
};


#endif //ROCKETLEAGUE_SERVERUPDATEWORLD_H

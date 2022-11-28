//
// Created by roby on 25/11/22.
//

#ifndef ROCKETLEAGUE_SERVERUPDATEWORLD_H
#define ROCKETLEAGUE_SERVERUPDATEWORLD_H

#include "ServerUpdate.h"

class ServerUpdateWorld : public ServerUpdate{
public:
    ServerUpdateWorld(uint16_t &id, uint16_t &returnCode, const uint16_t &n, std::vector<uint16_t> &returnData) :
                                    ServerUpdate(id,returnCode,returnData){};
    ~ServerUpdateWorld() override = default;

    uint16_t getType() const override;
    std::vector<uint16_t> beSerialized() override;
};


#endif //ROCKETLEAGUE_SERVERUPDATEWORLD_H

//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_SERVERCREATEACK_H
#define ROCKETLEAGUE_SERVERCREATEACK_H

#include "ServerUpdate.h"

class ServerCreateACK : public ServerUpdate{
public:
    ServerCreateACK(const uint16_t &id, uint16_t &returnCode) : ServerUpdate(id, returnCode){};
    ~ServerCreateACK() override = default;

    uint16_t getType() const override;
    std::vector<uint16_t> beSerialized() override;

};


#endif //ROCKETLEAGUE_SERVERCREATEACK_H

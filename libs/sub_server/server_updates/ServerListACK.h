//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_SERVERLISTACK_H
#define ROCKETLEAGUE_SERVERLISTACK_H

#include "ServerUpdate.h"

class ServerListACK : public ServerUpdate{
public:
    ServerListACK(uint8_t &id, std::string &returnData) : ServerUpdate(id,returnData) {};
    ~ServerListACK() override = default;

    uint8_t getType() const override;
    std::vector<uint8_t> beSerialized() override;
};


#endif //ROCKETLEAGUE_SERVERLISTACK_H

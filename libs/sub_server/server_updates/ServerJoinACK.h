//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_SERVERJOINACK_H
#define ROCKETLEAGUE_SERVERJOINACK_H

#include "ServerUpdate.h"

class ServerJoinACK : public ServerUpdate{
public:
//    ServerJoinACK(uint8_t &id, std::string &returnData) : ServerUpdate(id,returnData) {};
    ServerJoinACK(uint8_t &id, std::vector<uint8_t> &returnData) : ServerUpdate(id,returnData) {};
    ~ServerJoinACK() override = default;

    uint8_t getType() const override;
    std::vector<uint8_t> beSerialized() override;
};


#endif //ROCKETLEAGUE_SERVERJOINACK_H

//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_SERVERCREATEACK_H
#define ROCKETLEAGUE_SERVERCREATEACK_H

#include "ServerUpdate.h"

class ServerCreateACK : public ServerUpdate{
public:
    ServerCreateACK(uint8_t &id, std::vector<uint8_t> &data) : ServerUpdate(id,data) {};
    ~ServerCreateACK() override = default;

    uint8_t getType() const override;
    std::vector<uint8_t> beSerialized() override;

};


#endif //ROCKETLEAGUE_SERVERCREATEACK_H

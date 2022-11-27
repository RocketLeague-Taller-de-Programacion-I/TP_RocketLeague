//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTJOINACK_H
#define ROCKETLEAGUE_CLIENTJOINACK_H

#include "ClientUpdate.h"

class ClientJoinACK : public ClientUpdate{
public:
    ClientJoinACK(uint8_t &id, uint8_t &returnCode) : ClientUpdate(id,returnCode) {};
    ~ClientJoinACK() = default;
    uint8_t getType() const override { return JOIN_ACK; };
};


#endif //ROCKETLEAGUE_CLIENTJOINACK_H

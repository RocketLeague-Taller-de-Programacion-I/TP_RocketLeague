//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTJOINACK_H
#define ROCKETLEAGUE_CLIENTJOINACK_H

#include "ClientUpdate.h"

class ClientJoinACK : public ClientUpdate{
private:
    std::string returnCode;
public:
    ClientJoinACK(uint8_t &id, std::string &returnCode);
    ~ClientJoinACK() = default;
};


#endif //ROCKETLEAGUE_CLIENTJOINACK_H

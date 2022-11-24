//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_JOINACK_H
#define ROCKETLEAGUE_JOINACK_H

#include "GameUpdate.h"

class JoinACK : public GameUpdate{
private:
    std::string returnCode;
public:
    JoinACK(uint8_t &id, std::string &returnCode);
    ~JoinACK() = default;
};


#endif //ROCKETLEAGUE_JOINACK_H

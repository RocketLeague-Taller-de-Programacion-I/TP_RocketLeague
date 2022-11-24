//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_CREATEACK_H
#define ROCKETLEAGUE_CREATEACK_H

#include "GameUpdate.h"

class CreateACK : public GameUpdate{
private:
    std::string returnCode;
public:
    CreateACK(uint8_t &id, std::string &returnCode);
    ~CreateACK() = default;
};


#endif //ROCKETLEAGUE_CREATEACK_H

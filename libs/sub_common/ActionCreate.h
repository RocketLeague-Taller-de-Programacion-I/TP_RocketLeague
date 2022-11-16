//
// Created by lucaswaisten on 16/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONCREATE_H
#define ROCKETLEAGUE_ACTIONCREATE_H


#include "Action.h"

class ActionCreate : public Action {

public:
    ActionCreate(uint8_t id, uint8_t c, std::string name);
};


#endif //ROCKETLEAGUE_ACTIONCREATE_H

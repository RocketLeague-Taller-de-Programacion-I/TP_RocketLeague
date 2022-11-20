//
// Created by lucaswaisten on 20/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONMOVE_H
#define ROCKETLEAGUE_ACTIONMOVE_H


#include "Action.h"

class ActionMove : public Action {
private:
    uint8_t type;
public:
    void execute(Match &match) override;


};


#endif //ROCKETLEAGUE_ACTIONMOVE_H

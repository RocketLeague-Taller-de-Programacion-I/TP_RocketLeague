//
// Created by lucaswaisten on 20/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONMOVE_H
#define ROCKETLEAGUE_ACTIONMOVE_H

#include "ActionUpdate.h"
#include "../../sub_server/Match.h"
#include "Action.h"

class ActionMove : public Action {
private:
    uint8_t type;
public:
    virtual void executeMove(Match &match, std::function<void(ActionUpdate *update)> updateClientSender);
};


#endif //ROCKETLEAGUE_ACTIONMOVE_H

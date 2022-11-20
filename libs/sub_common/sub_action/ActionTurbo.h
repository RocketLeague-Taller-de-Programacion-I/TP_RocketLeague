//
// Created by lucaswaisten on 20/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONTURBO_H
#define ROCKETLEAGUE_ACTIONTURBO_H


#include "ActionMove.h"

class ActionTurbo : public ActionMove {
public:
    void executeMove(Match &match, std::function<void(ActionUpdate *update)> updateClientSender) override;
};


#endif //ROCKETLEAGUE_ACTIONTURBO_H

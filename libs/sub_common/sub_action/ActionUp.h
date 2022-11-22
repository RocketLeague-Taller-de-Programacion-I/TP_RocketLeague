//
// Created by lucaswaisten on 20/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONUP_H
#define ROCKETLEAGUE_ACTIONUP_H


#include "ActionMove.h"

class ActionUp : public ActionMove {
public:
    void executeMove(Match &match, std::function<void(ActionUpdate *update)> updateClientSender) override;
};


#endif //ROCKETLEAGUE_ACTIONUP_H

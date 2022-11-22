//
// Created by lucaswaisten on 20/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONLEFT_H
#define ROCKETLEAGUE_ACTIONLEFT_H

#include "ActionMove.h"

class ActionLeft : public ActionMove{
    void executeMove(Match &match, std::function<void(ActionUpdate *update)> updateClientSender) override;
};


#endif //ROCKETLEAGUE_ACTIONLEFT_H

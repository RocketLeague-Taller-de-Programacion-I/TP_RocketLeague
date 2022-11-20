//
// Created by lucaswaisten on 20/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONJUMP_H
#define ROCKETLEAGUE_ACTIONJUMP_H


#include "ActionMove.h"

class ActionJump : public ActionMove{
public:
    void executeMove(Match &match, std::function<void(ActionUpdate *update)> updateClientSender) override;
};


#endif //ROCKETLEAGUE_ACTIONJUMP_H

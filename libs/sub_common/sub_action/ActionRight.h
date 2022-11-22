//
// Created by lucaswaisten on 20/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONRIGHT_H
#define ROCKETLEAGUE_ACTIONRIGHT_H


#include "ActionMove.h"

class ActionRight : public ActionMove{
public:
    void executeMove(Match &match, std::function<void(ActionUpdate *update)> updateClientSender) override;
};


#endif //ROCKETLEAGUE_ACTIONRIGHT_H

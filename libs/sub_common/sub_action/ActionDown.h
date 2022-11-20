//
// Created by lucaswaisten on 20/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONDOWN_H
#define ROCKETLEAGUE_ACTIONDOWN_H


#include "ActionMove.h"

class ActionDown : public ActionMove {
public:
    void executeMove(Match &match, std::function<void(ActionUpdate *update)> updateClientSender) override;
};


#endif //ROCKETLEAGUE_ACTIONDOWN_H

//
// Created by lucaswaisten on 20/11/22.
//

#include "ActionTurbo.h"

void ActionTurbo::executeMove(Match &match, std::function<void(ActionUpdate *update)> updateClientSender) {
    match.moveTurbo(idCreator,updateClientSender);
}

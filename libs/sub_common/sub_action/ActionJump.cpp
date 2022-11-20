//
// Created by lucaswaisten on 20/11/22.
//

#include "ActionJump.h"

void ActionJump::executeMove(Match &match, std::function<void(ActionUpdate *update)> updateClientSender) {
    match.moveJump(idCreator,updateClientSender);
}

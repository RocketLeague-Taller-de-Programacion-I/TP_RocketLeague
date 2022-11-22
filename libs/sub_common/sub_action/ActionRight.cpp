//
// Created by lucaswaisten on 20/11/22.
//

#include "ActionRight.h"

void ActionRight::executeMove(Match &match, std::function<void(ActionUpdate *update)> updateClientSender) {
    match.moveRight(idInvoker,updateClientSender);
}

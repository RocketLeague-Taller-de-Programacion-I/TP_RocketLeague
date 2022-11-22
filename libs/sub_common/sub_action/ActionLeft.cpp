//
// Created by lucaswaisten on 20/11/22.
//

#include "ActionLeft.h"

void ActionLeft::executeMove(Match &match, std::function<void(ActionUpdate *)> updateClientSender) {
    match.moveLeft(idCreator,updateClientSender);
}

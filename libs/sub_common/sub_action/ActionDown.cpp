//
// Created by lucaswaisten on 20/11/22.
//

#include "ActionDown.h"

void ActionDown::executeMove(Match &match, std::function<void(ActionUpdate *update)> updateClientSender) {
    match.moveDown(idCreator,updateClientSender);
}

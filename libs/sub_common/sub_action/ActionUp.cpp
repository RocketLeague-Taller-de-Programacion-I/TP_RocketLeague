//
// Created by lucaswaisten on 20/11/22.
//

#include "ActionUp.h"

void ActionUp::executeMove(Match &match, std::function<void(ActionUpdate *update)> updateClientSender) {
    match.jump(idInvoker,updateClientSender);
}

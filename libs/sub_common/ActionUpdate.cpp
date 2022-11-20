//
// Created by roby on 19/11/22.
//

#include "ActionUpdate.h"

ActionUpdate::ActionUpdate(uint8_t& id, std::string& name) : Action(id, name){}

void ActionUpdate::execute(GameManager &gameManager,
                           std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> startClientThreads) {
}

ActionUpdate::~ActionUpdate() = default;

std::string ActionUpdate::getGameName() {
    return nameGame;
}

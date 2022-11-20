//
// Created by roby on 19/11/22.
//

#include "ActionUpdate.h"
#include "protocolo.h"

ActionUpdate::ActionUpdate(uint8_t& id, std::string& name) : Action(id, name){}

void ActionUpdate::execute(GameManager &gameManager,
                           const std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> &setQueue) {
}

ActionUpdate::~ActionUpdate() = default;

std::string ActionUpdate::getGameName() {
    return nameGame;
}

std::vector<uint8_t> ActionUpdate::beSerialized() {
    std::vector<uint8_t> dummyData;
    return Protocolo::serializeUpdateAction(dummyData);
}

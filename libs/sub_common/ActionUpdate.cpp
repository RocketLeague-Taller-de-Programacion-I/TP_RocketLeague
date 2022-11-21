//
// Created by roby on 19/11/22.
//

#include "ActionUpdate.h"
#include "protocolo.h"

ActionUpdate::ActionUpdate(uint8_t& id, std::string& returnMessage) : Action(id, returnMessage){}

void ActionUpdate::execute(GameManager &gameManager,
                           const std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> &setQueue) {
}

ActionUpdate::~ActionUpdate() = default;

std::string ActionUpdate::getGameName() {
    return nameGame;
}

std::vector<uint8_t> ActionUpdate::beSerialized() {
    std::vector<uint8_t> updateData;
    updateData.push_back(idCreator);
    updateData.insert(updateData.end(), nameGame.begin(), nameGame.end());
    return Protocolo::serializeUpdateAction(updateData);
}

uint8_t ActionUpdate::getIdCreatorGame() {
    return idCreator;
}

uint8_t ActionUpdate::getType() const {
    return UPDATE;
}

uint8_t ActionUpdate::getX() {
    return 0;
}

uint8_t ActionUpdate::getY() {
    return 0;
}

uint8_t ActionUpdate::getAngle() {
    return 0;
}

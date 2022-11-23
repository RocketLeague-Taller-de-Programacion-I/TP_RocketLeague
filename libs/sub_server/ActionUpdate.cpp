//
// Created by roby on 19/11/22.
//

#include "ActionUpdate.h"
#include "protocolo.h"

ActionUpdate::ActionUpdate(uint8_t& id, std::string& returnMessage) : Action(id, returnMessage){}
// TODO: tiene que tener ID y return code
/*Action * ActionUpdate::execute(GameManager &gameManager,
                               const std::function<BlockingQueue<Action *> *(BlockingQueue<Action *> *)> &setQueue) {
    return this;
}
 */

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

std::string ActionUpdate::getReturnMessage() {
    return nameGame;
}

Action *ActionUpdate::execute(GameManager &gameManager,
                              const std::function<BlockingQueue<Action *> *(ProtectedQueue<Action *> *)> &setQueue) {
    return nullptr;
}

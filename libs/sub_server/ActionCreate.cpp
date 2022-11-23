//
// Created by lucaswaisten on 16/11/22.
//

#include "ActionCreate.h"
#include "sub_server/gameManager.h"
#include "protocolo.h"

ActionCreate::ActionCreate(uint8_t &id,
                           uint8_t &c,
                           const std::string &name) : Action(id,
                                                             c,
                                                             name) {}

std::string ActionCreate::getGameName() {
    return nameGame;
}

uint8_t ActionCreate::getCapacity() {
    return capacityGame;
}

uint8_t ActionCreate::getIdCreatorGame() {
    return idCreator;
}

//Action * ActionCreate::execute(GameManager &gameManager, const std::function<BlockingQueue<Action *> *(
//        BlockingQueue<Action *> *)> &setQueue) {
//    gameManager.createGame(idCreator, capacityGame, nameGame, setQueue);
//
//}

uint8_t ActionCreate::getType() const {
    return CREATE_ROOM;
}

std::vector<uint8_t> ActionCreate::beSerialized() {
    // create a string from the name and the capacity
    std::string nameCapacity = std::to_string(capacityGame) + nameGame;
    std::vector<uint8_t> createData(nameCapacity.begin(), nameCapacity.end());
    return Protocolo::serializeCreateAction(createData);
}
std::string ActionCreate::getReturnMessage() {
    return nameGame;
}

Action *ActionCreate::execute(GameManager &gameManager,
                              const std::function<BlockingQueue<Action *> *(ProtectedQueue<Action *> *)> &setQueue) {

    gameManager.createGame(idCreator, capacityGame, nameGame, setQueue);
    std::string returnMessage = "OK";
    return new ActionUpdate(idCreator, returnMessage);
}

ActionCreate::~ActionCreate() = default;

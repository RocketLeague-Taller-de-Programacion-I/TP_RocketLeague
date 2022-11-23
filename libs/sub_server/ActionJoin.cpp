//
// Created by lucaswaisten on 16/11/22.
//

#include "ActionJoin.h"
#include "protocolo.h"

ActionJoin::ActionJoin(uint8_t &id, std::string &name) : Action(id, std::move(name)){}

std::string ActionJoin::getGameName() {
    return nameGame;
}

uint8_t ActionJoin::getIdCreatorGame() {
    return idCreator;
}

//Action * ActionJoin::execute(GameManager &gameManager, const std::function<BlockingQueue<Action *> *(
//        BlockingQueue<Action *> *)> &setQueue) {
//   gameManager.joinGame(idCreator, nameGame, setQueue);
//}

uint8_t ActionJoin::getType() const {
    return JOIN_ROOM;
}

std::vector<uint8_t> ActionJoin::beSerialized() {
    std::vector<uint8_t> joinData(this->getGameName().begin(), this->getGameName().end());
    return Protocolo::serializeJoinAction(joinData);
}
std::string ActionJoin::getReturnMessage() {
    return nameGame;
}

ActionJoin::~ActionJoin() = default;

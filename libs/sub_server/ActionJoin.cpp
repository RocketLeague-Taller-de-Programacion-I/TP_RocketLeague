//
// Created by lucaswaisten on 16/11/22.
//

#include "ActionJoin.h"
#include "sub_server/gameManager.h"
#include "protocolo.h"

ActionJoin::ActionJoin(uint8_t &id, std::string &name) : ActionUpdate(id, name){}

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
    std::vector<uint8_t> joinData;
    joinData.emplace_back(this->getType());
    joinData.emplace_back(this->idCreator);
    joinData.insert(joinData.end(),this->nameGame.begin(), this->nameGame.end());
    return joinData;
}
std::string ActionJoin::getReturnMessage() {
    return nameGame;
}

Action *ActionJoin::execute(GameManager &gameManager,
                            const std::function<BlockingQueue<Action *> *(ProtectedQueue<Action *> *)> &setQueue) {
    std::string message = "OK";
    if(!gameManager.joinGame(idCreator, nameGame, setQueue)) {
        message = "ERROR";
    }
    return new ActionJoin(idCreator, message);
}

ActionJoin::~ActionJoin() = default;

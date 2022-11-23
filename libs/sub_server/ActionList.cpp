//
// Created by lucaswaisten on 16/11/22.
//

#include "ActionList.h"
#include "sub_server/gameManager.h"
#include "protocolo.h"

ActionList::ActionList(uint8_t id) : Action(id,""){}


uint8_t ActionList::getIdCreatorGame() {
    return idCreator;
}

uint8_t ActionList::getType() const {
    return LIST_ROOMS;
}

std::vector<uint8_t> ActionList::beSerialized() {
    std::vector<uint8_t> dummyData;
    return Protocolo::serializeListAction(dummyData);
}
std::string ActionList::getReturnMessage() {
    return nameGame;
}

Action *ActionList::execute(GameManager &manager,
                            const std::function<BlockingQueue<Action *> *(ProtectedQueue<Action *> *)> &setQueue) {
    std::string list = manager.listGames(idCreator);
    return new ActionUpdate(idCreator, list);
}

ActionList::~ActionList() = default;

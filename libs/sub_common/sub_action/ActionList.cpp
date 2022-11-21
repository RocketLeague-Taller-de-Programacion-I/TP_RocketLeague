//
// Created by lucaswaisten on 16/11/22.
//

#include "ActionList.h"
#include "sub_server/gameManager.h"
#include "../protocolo.h"

ActionList::ActionList(uint8_t id) : Action(id,""){}


uint8_t ActionList::getIdCreatorGame() {
    return idCreator;
}

void ActionList::execute(GameManager &manager, const std::function<void(BlockingQueue<Action *> *,
                                                                        BlockingQueue<Action *> *)> &setQueue) {
}

uint8_t ActionList::getType() const {
    return LIST_ROOMS;
}

std::vector<uint8_t> ActionList::beSerialized() {
    std::vector<uint8_t> dummyData;
    return Protocolo::serializeListAction(dummyData);
}

ActionList::~ActionList() = default;

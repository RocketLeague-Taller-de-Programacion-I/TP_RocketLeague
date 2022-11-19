//
// Created by lucaswaisten on 16/11/22.
//

#include "ActionList.h"

ActionList::ActionList(uint8_t id) : Action(id,0,""){

}


uint8_t ActionList::getIdCreatorGame() {
    return idCreator;
}

void ActionList::execute(GameManager &manager, std::function<void(BlockingQueue<Action> *)> setQueue) {
    Action::execute(manager, setQueue);
}

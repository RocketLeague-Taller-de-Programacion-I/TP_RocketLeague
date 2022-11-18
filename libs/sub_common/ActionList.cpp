//
// Created by lucaswaisten on 16/11/22.
//

#include "ActionList.h"

ActionList::ActionList(uint8_t id) : Action(id,0,""){

}

void ActionList::execute(GameManager &gameManager, ClientManager *pClientManager) {
    Action::execute(gameManager, pClientManager);
}

uint8_t ActionList::getIdCreatorGame() {
    return idCreator;
}
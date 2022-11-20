//
// Created by lucaswaisten on 16/11/22.
//

#include "ActionJoin.h"

#include <utility>

ActionJoin::ActionJoin(uint8_t &id, std::string &name) : Action(id, std::move(name)){

}


std::string ActionJoin::getGameName() {
    return nameGame;
}

uint8_t ActionJoin::getIdCreatorGame() {
    return idCreator;
}

void ActionJoin::execute(GameManager &gameManager, std::function<void(BlockingQueue<Action *> *,
                                                                      BlockingQueue<Action *> *)> startClientThreads) {
    gameManager.joinGame(idCreator, std::move(nameGame), startClientThreads);
}

ActionJoin::~ActionJoin() = default;

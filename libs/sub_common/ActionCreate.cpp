//
// Created by lucaswaisten on 16/11/22.
//

#include "ActionCreate.h"

#include <utility>

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

void ActionCreate::execute(GameManager &gameManager, std::function<void(BlockingQueue<Action *> *,BlockingQueue<Action *> *)> startClientThreads) {
    gameManager.createGame(idCreator, capacityGame, std::move(nameGame), startClientThreads);
}

ActionCreate::~ActionCreate() = default;

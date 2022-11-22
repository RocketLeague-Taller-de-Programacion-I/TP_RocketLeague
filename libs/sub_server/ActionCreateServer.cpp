//
// Created by lucaswaisten on 16/11/22.
//

#include "ActionCreateServer.h"
#include <utility>
#include "sub_common/protocolo.h"

ActionCreateServer::ActionCreateServer(uint8_t &id, int &c, const std::string &name, GameManager &gameManager,
                                       std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> function) :
                           Action(id), gameManager(gameManager),startClientThreads(std::move(function)),capacityGame(c), nameGame(name) {}

std::string ActionCreateServer::getGameName() {
    return nameGame;
}

int ActionCreateServer::getCapacity() const {
    return capacityGame;
}

void ActionCreateServer::execute() {
    gameManager.createGame(idInvoker,capacityGame,nameGame,startClientThreads);
}

std::vector<uint8_t> ActionCreateServer::beSerialized() {
    // create a string from the name and the capacity
    std::string nameCapacity = std::to_string(capacityGame) + nameGame;
    std::vector<uint8_t> createData(nameCapacity.begin(), nameCapacity.end());
    return Protocolo::serializeCreateAction(createData);
}

ActionCreateServer::~ActionCreateServer() = default;

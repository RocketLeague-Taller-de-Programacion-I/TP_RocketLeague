//
// Created by lucaswaisten on 16/11/22.
//

#include "ActionJoinServer.h"

#include <utility>
#include "sub_common/protocolo.h"

ActionJoinServer::ActionJoinServer(uint8_t &id, std::string &name, GameManager &manager,
                                   std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> function) :
        Action(id), gameManager(manager),
        startClientThreads(std::move(function)), nameGame(name){}

std::string ActionJoinServer::getGameName() {
    return nameGame;
}

void ActionJoinServer::execute() {
    gameManager.joinGame(idInvoker, nameGame, startClientThreads);
}

std::vector<uint8_t> ActionJoinServer::beSerialized() {
    std::vector<uint8_t> joinData(this->getGameName().begin(), this->getGameName().end());
    return Protocolo::serializeJoinAction(joinData);
}

ActionJoinServer::~ActionJoinServer() = default;

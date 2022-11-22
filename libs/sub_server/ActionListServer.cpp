//
// Created by lucaswaisten on 16/11/22.
//

#include "ActionListServer.h"
#include "sub_common/protocolo.h"

ActionListServer::ActionListServer(uint8_t id, GameManager &manager,
                                   std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> function) : Action(id),
                                                                                                             gameManager(manager),
                                                                                                             startClientThreads(std::move(function)){}


void ActionListServer::execute() {
    gameManager.listGames();
}

std::vector<uint8_t> ActionListServer::beSerialized() {
    std::vector<uint8_t> dummyData;
    return Protocolo::serializeListAction(dummyData);
}

ActionListServer::~ActionListServer() = default;

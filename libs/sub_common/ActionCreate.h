//
// Created by lucaswaisten on 16/11/22.
//
#pragma once

#ifndef ROCKETLEAGUE_ACTIONCREATE_H
#define ROCKETLEAGUE_ACTIONCREATE_H

#include <utility>
#include "Action.h"

class ActionCreate : public Action {

public:
    ActionCreate(uint8_t &id, uint8_t &c, const std::string &name);
    ~ActionCreate() override;

    std::string getGameName() override;

    void execute(GameManager &gameManager, std::function<void(BlockingQueue<Action *> *,BlockingQueue<Action *> *)> startClientThreads) override;

    uint8_t getCapacity() override;

    uint8_t getIdCreatorGame() override;
};


#endif //ROCKETLEAGUE_ACTIONCREATE_H

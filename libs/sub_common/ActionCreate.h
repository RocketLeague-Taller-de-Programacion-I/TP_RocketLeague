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
    ActionCreate(uint8_t id, uint8_t c, std::string name);

    std::string getGameName() override;

    void execute(GameManager &gameManager, ClientManager *pClientManager) override;

    uint8_t getCapacity() override;

    uint8_t getIdCreatorGame() override;
};


#endif //ROCKETLEAGUE_ACTIONCREATE_H

//
// Created by lucaswaisten on 16/11/22.
//
#pragma once

#ifndef ROCKETLEAGUE_ACTIONJOIN_H
#define ROCKETLEAGUE_ACTIONJOIN_H

#include "Action.h"

class ActionJoin : public Action {

public:
    ActionJoin(uint8_t id, std::string name);
    void execute(GameManager &gameManager, ClientManager *pClientManager) override;

    std::string getGameName() override;

    uint8_t getIdCreatorGame() override;
};


#endif //ROCKETLEAGUE_ACTIONJOIN_H

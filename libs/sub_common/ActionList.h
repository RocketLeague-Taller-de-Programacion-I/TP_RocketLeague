//
// Created by lucaswaisten on 16/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONLIST_H
#define ROCKETLEAGUE_ACTIONLIST_H


#include "Action.h"

class ActionList : public Action{

public:
    explicit ActionList(uint8_t id);
    void execute(GameManager &gameManager, ClientManager *pClientManager) override;

    uint8_t getIdCreatorGame() override;
};


#endif //ROCKETLEAGUE_ACTIONLIST_H

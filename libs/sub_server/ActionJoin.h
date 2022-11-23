//
// Created by lucaswaisten on 16/11/22.
//
#pragma once

#ifndef ROCKETLEAGUE_ACTIONJOIN_H
#define ROCKETLEAGUE_ACTIONJOIN_H

#include "Action.h"

class ActionJoin : public Action {

public:
    ActionJoin(uint8_t &id, std::string &name);
    ~ActionJoin() override;

    std::string getGameName() override;
    uint8_t getIdCreatorGame() override;
    uint8_t getType() const override;
    Action * execute(GameManager &gameManager, const std::function<BlockingQueue<Action *> *(
            ProtectedQueue<Action *> *)> &setQueue);
    std::vector<uint8_t> beSerialized() override;

    std::string getReturnMessage();
};


#endif //ROCKETLEAGUE_ACTIONJOIN_H

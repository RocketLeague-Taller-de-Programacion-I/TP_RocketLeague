//
// Created by lucaswaisten on 12/11/22.
//
#pragma once

class GameManager;

#ifndef ROCKETLEAGUE_ACTION_H
#define ROCKETLEAGUE_ACTION_H

#include <utility>
#include <cstdint>
#include <string>
#include <vector>
#include <functional>
#include "sub_common/BlockingQueue.h"
#include "sub_common/ProtectedQueue.h"

enum actionType {
    CREATE_ROOM = 1,
    JOIN_ROOM,
    LIST_ROOMS,
    MOVE,
    UPDATE
};


class Action {
protected:
    uint8_t idCreator;
    uint8_t capacityGame;
    std::string nameGame;
public:
    Action();
    Action(uint8_t &id, uint8_t &c, std::string name);
    Action(uint8_t &id, std::string name);

    virtual ~Action();
    virtual std::string getGameName();

    virtual uint8_t getCapacity();

    virtual uint8_t getIdCreatorGame();
    virtual std::uint8_t getType() const;
    virtual std::string getNameGame() const;

    Action * execute(GameManager &manager, const std::function<BlockingQueue<Action *> *(BlockingQueue<Action *> *)> &setQueue);
    virtual std::vector<uint8_t> beSerialized() = 0;

    virtual std::string getReturnMessage() = 0;

};



#endif //ROCKETLEAGUE_ACTION_H

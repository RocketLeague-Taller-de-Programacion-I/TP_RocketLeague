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
#include "../BlockingQueue.h"


enum actionType {
    CREATE_ROOM = 1,
    JOIN_ROOM,
    LIST_ROOMS,
    MOVE,
    UPDATE
};


class Action {
protected:
    int idCreator;
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

    virtual void execute(GameManager &manager, const std::function<void(BlockingQueue<Action *> *,BlockingQueue<Action *> *)> &setQueue) = 0;
    virtual std::vector<uint8_t> beSerialized() = 0;
};


#endif //ROCKETLEAGUE_ACTION_H

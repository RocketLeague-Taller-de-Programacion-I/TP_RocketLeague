//
// Created by lucaswaisten on 12/11/22.
//
#pragma once

#ifndef ROCKETLEAGUE_ACTION_H
#define ROCKETLEAGUE_ACTION_H

#include <cstdint>
#include <string>
#include <vector>
#include <functional>
#include "sub_server/gameManager.h"

enum actionType {
    CREATE_ROOM,
    JOIN_ROOM,
    LIST_ROOMS,
    MOVE
};

enum action {
    NOP,
    JUMP,
    RIGHT,
    LEFT,
    UP,
    DOWN,
    TURBO
} ;

class GameManager;
class Match;

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

    virtual void execute(GameManager &manager, std::function<void(BlockingQueue<Action *> *,BlockingQueue<Action *> *)> startClientThreads);

    virtual void executeMove(Match &match, std::function<void(ActionUpdate *update)> updateClientSender);

};


#endif //ROCKETLEAGUE_ACTION_H

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
   // explicit Action(const std::uint8_t &type, std::vector<char>& data);
   // explicit Action(const std::uint8_t &type, std::string & data);
    std::uint8_t getType() const;
    /*
     * agregar destructor virtual
     */
    /*
     * smart pointer
     */

    virtual void execute(GameManager &manager, std::function<void(BlockingQueue<Action *> *,BlockingQueue<Action *> *)> setQueue);
};


#endif //ROCKETLEAGUE_ACTION_H

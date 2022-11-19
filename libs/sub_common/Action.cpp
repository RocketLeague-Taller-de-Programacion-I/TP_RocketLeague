//
// Created by lucaswaisten on 12/11/22.
//

#include "Action.h"
#include <utility>

/*
Action::Action(const uint8_t &type,
               std::vector<char> &data){}

Action::Action(const uint8_t &type,
               std::string &data){}
*/
std::uint8_t Action::getType() const {
   return 0;
}

Action::Action() : idCreator(0),
                    capacityGame(0),
                    nameGame("") {}

Action::Action(uint8_t id,
               uint8_t c,
               std::string  name) :
               idCreator(id),
               capacityGame(c),
               nameGame(std::move(name)) {}

std::string Action::getGameName() {
    return std::string();
}

uint8_t Action::getCapacity() {
    return 0;
}

uint8_t Action::getIdCreatorGame() {
    return 0;
}

void Action::execute(GameManager &manager,
                     std::function<void(BlockingQueue<Action> *)> setQueue) {}



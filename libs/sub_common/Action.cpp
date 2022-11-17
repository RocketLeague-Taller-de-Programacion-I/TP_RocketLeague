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
   // return type;
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
    return nameGame;
}

uint8_t Action::getCapacity() {
    return capacityGame;
}

uint8_t Action::getIdCreatorGame() {
    return idCreator;
}



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

void Action::excecute(GameManager &manager, ClientManager *i) {
/*
    switch (this->type) {
        case CREATE_ROOM:
            manager.createGame(this->data, i);
        case JOIN_ROOM:
            manager.joinGame(this->data, i);
        case LIST_ROOMS:
            manager.listGames();
        case MOVE:
            manager.move(this->data, i);
    }*/
}

Action::Action() {

}

Action::Action(uint8_t id, uint8_t c, std::string  name) : idCreator(id), capacityGame(c),nameGame(std::move(name)){}


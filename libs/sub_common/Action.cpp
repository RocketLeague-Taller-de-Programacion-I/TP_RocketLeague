//
// Created by lucaswaisten on 12/11/22.
//

#include "Action.h"


Action::Action(const uint8_t &type,
               std::vector<char> &data) :
               type(type),
               data(data) {}

Action::Action(const uint8_t &type,
               std::string &data)
        : type(type),
          data(data.begin(),
               data.end()) {}

std::uint8_t Action::getType() const {
    return type;
}

std::string Action::excecute(GameManager &manager) {
    switch (this->type) {
        case CREATE_ROOM:
            return manager.createGame(this->data);
        case JOIN_ROOM:
            return manager.joinGame(this->data);
        case LIST_ROOMS:
            return manager.listGames();
        case MOVE:
            return manager.move(this->data);
    }
    return {};
}


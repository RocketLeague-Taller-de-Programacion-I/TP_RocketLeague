//
// Created by lucaswaisten on 12/11/22.
//

#include "Action.h"


Action::Action(const uint8_t &type,
               std::vector<char> &data) : Information(type,data){}

Action::Action(const uint8_t &type,
               std::string &data) : Information(type,std::vector<char>(data.begin(),data.end())){}

std::uint8_t Action::getType() const {
    return type;
}

void Action::excecute(GameManager &manager, ClientManager *i) {

    switch (this->type) {
        case CREATE_ROOM:
            manager.createGame(this->data, i);
        case JOIN_ROOM:
            manager.joinGame(this->data, i);
        case LIST_ROOMS:
            manager.listGames();
        case MOVE:
            manager.move(this->data, i);
    }
}


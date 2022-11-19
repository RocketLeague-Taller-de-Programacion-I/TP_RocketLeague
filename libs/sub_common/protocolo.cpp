//
// Created by lucaswaisten on 04/11/22.
//

#include "protocolo.h"
#include <sstream>
#include <regex>
/*
 * Hilo de sender popea de la cola de acciones
        Llama protocolo(Action)
Protocolo serializa la acción
devuelve un vector de char
        Hilo de sender envía el vector de char
        command_t Protocolo::getMapCommand(Action action) { //procesa la accion y devuelve un vector de char}*/
std::vector<uint8_t> Protocolo::serializeAction(Action *action) {
    std::vector<uint8_t> result;
    result.emplace_back(action->getType());
    if (action->getType() == CREATE_ROOM) {
        parseCreateRoomData(action, result);
        return result;
    } else if (action.getType() == MOVE) {
        //insertar id del jugador previamente otorgado
    }
   // result.insert(result.end(), action.data.begin(), action.data.end());
    return result;
}

void Protocolo::parseCreateRoomData(Action *action, std::vector<uint8_t> &result) const {
   // std::string data (action.data.begin(), action.data.end());
    std::regex number("[0-9]+");
    std::smatch match;
   // std::regex_search(data, match, number);

    int players = match.str().empty() ? 0 : std::stoi(match.str());
    result.emplace_back(players);
    //std::string name = data.substr(0, data.find(match.str()));

   // result.insert(result.end(), name.begin(), name.end());
}

command_t Protocolo::getMapCommand(uint32_t action) {
    return this->mapCommand.at(action);
}

std::unique_ptr<Action> Protocolo::deserializarData(const std::vector<uint8_t>& data) {
    uint8_t type(data[1]);

    switch (type) {
        case CREATE_ROOM:
            return parseCreateAction(data);
        case JOIN_ROOM:
            return parseJoinAction(data);
        case LIST_ROOMS:
            return parseListAction(data);
    }
    return {};
}

std::unique_ptr<Action> Protocolo::parseCreateAction(const std::vector<uint8_t> &data) {
    uint8_t id(data[0]);
    uint8_t capacity(data[2]);
    std::string name(data.begin()+3,data.end());
    std::unique_ptr<Action> pAction(new ActionCreate(id, capacity, std::move(name)));
    return pAction;
}

std::unique_ptr<Action> Protocolo::parseJoinAction(const std::vector<uint8_t> &data) {
    uint8_t id(data[0]);
    std::string name(data.begin()+2,data.end());
    std::unique_ptr<Action> pAction(new ActionJoin(id, std::move(name)));
    return pAction;
}

std::unique_ptr<Action> Protocolo::parseListAction(const std::vector<uint8_t> &data) {
    uint8_t id(data[0]);
    std::unique_ptr<Action> pAction(new ActionList(id));
    return pAction;
}

//
// Created by lucaswaisten on 04/11/22.
//

#include "protocolo.h"

command_t Protocolo::getMapCommand(uint32_t action) {
    return this->mapCommand.at(action);
}

ServerAction * Protocolo::deserializeData(const std::vector<uint8_t>& data) {
    uint8_t type(data[1]);
    switch (type) {
        case CREATE_ROOM:
            return parseCreateAction(data);
        case JOIN_ROOM:
            return parseJoinAction(data);
        case LIST_ROOMS:
            return parseListAction(data);
//        case MOVE:
//            return parseUpdateAction(data);
    }
    return {};
}
/*
 * [0] -> id
 * [1] -> type
 * [2] -> playersRequired
 * [3] -> [end] -> string
 *
 */
ServerAction * Protocolo::parseCreateAction(const std::vector<uint8_t> &data) {
    uint8_t id = data[0];
    uint8_t capacity(data[2]);
    std::string name(data.begin()+3,data.end());

//    Action* pAction = new ActionCreate(id, capacity, name);
    ServerAction* pAction = new ServerCreateRoom(id, capacity, name);
    return pAction;
}

ServerAction * Protocolo::parseJoinAction(const std::vector<uint8_t> &data) {
    uint8_t id = data[0];
    std::string name(data.begin()+2,data.end());
    //strip last spaces from name
    std::string stripped = name.substr(0, name.find_last_of(' '));
//    Action* pAction = new ActionJoin(id, stripped);
    ServerAction* pAction = new ServerJoinRoom(id, stripped);
    return pAction;
}

ServerAction * Protocolo::parseListAction(const std::vector<uint8_t> &data) {
    uint8_t id = data[0];
//    Action* pAction = new ActionList(id, gameList);
    ServerAction* pAction = new ServerListRooms(id);
    return pAction;
}

std::vector<uint8_t> Protocolo::serializeCreateAction(const std::vector<uint8_t> &data) {
    std::vector<uint8_t> result;
    result.emplace_back(CREATE_ROOM); //type
    result.emplace_back(1); //id to be received
    result.insert(result.end(), data.begin(), data.end());
    return result;
}

std::vector<uint8_t> Protocolo::serializeUpdateAction(const std::vector<uint8_t> &data) {

    std::vector<uint8_t> result;
    //TODO: cambiar el UPDATE
    result.emplace_back(1);
    result.insert(result.end(),data.begin(),data.end());
    return result;
}

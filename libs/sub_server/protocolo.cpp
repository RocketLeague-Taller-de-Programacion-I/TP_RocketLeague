//
// Created by lucaswaisten on 04/11/22.
//

#include "sub_server/Action.h"
#include "protocolo.h"
#include "sub_server/ActionCreate.h"
#include "sub_server/ActionList.h"
#include "sub_server/ActionJoin.h"
#include "sub_server/ActionUpdate.h"

#include <sstream>
#include <regex>

std::vector<uint8_t> Protocolo::serializeAction(Action *action) {
    return action->beSerialized();
}

command_t Protocolo::getMapCommand(uint32_t action) {
    return this->mapCommand.at(action);
}

Action * Protocolo::deserializeData(const std::vector<uint8_t>& data) {
    uint8_t type(data[1]);
    switch (type) {
        case CREATE_ROOM:
            return parseCreateAction(data);
        case JOIN_ROOM:
            return parseJoinAction(data);
        case LIST_ROOMS:
            return parseListAction(data);
        case UPDATE:
            return parseUpdateAction(data);
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
Action* Protocolo::parseCreateAction(const std::vector<uint8_t> &data) {
    uint8_t id = data[0];
    uint8_t capacity(data[2]);
    std::string name(data.begin()+3,data.end());

    Action* pAction = new ActionCreate(id, capacity, name);
    return pAction;
}

Action * Protocolo::parseJoinAction(const std::vector<uint8_t> &data) {
    uint8_t id = data[0];
    std::string name(data.begin()+2,data.end());
    //strip last spaces from name
    std::string stripped = name.substr(0, name.find_last_of(' '));
    Action* pAction = new ActionJoin(id, stripped);
    return pAction;
}

Action * Protocolo::parseListAction(const std::vector<uint8_t> &data) {
    uint8_t id = data[0];
    Action* pAction = new ActionList(id);
    return pAction;
}

Action * Protocolo::parseUpdateAction(const std::vector<uint8_t> &vector) {;
    std::string data;
    if (not vector.empty()) {
        data = std::string(vector.begin()+2,vector.end());
    } else {
        data = "";
    }
    uint8_t id_que_hay_que_borrar = 0;
    Action* pAction = new ActionUpdate(id_que_hay_que_borrar, data);
    return pAction;
}

std::vector<uint8_t> Protocolo::serializeCreateAction(const std::vector<uint8_t> &data) {
    std::vector<uint8_t> result;
    result.emplace_back(CREATE_ROOM); //type
    result.emplace_back(1); //id to be received
    result.insert(result.end(), data.begin(), data.end());
    return result;
}

std::vector<uint8_t> Protocolo::serializeJoinAction(const std::vector<uint8_t> &data) {
    std::vector<uint8_t> result;
    result.emplace_back(JOIN_ROOM);
    result.insert(result.end(), data.begin(), data.end());
    return result;
}

std::vector<uint8_t> Protocolo::serializeListAction(const std::vector<uint8_t> &data) {
    std::vector<uint8_t> result;
    result.emplace_back(LIST_ROOMS);
//    result.insert(result.end(),data.begin(),data.end());
    return result;
}

std::vector<uint8_t> Protocolo::serializeMoveAction(const std::vector<uint8_t> &data) {
    return std::vector<uint8_t>();
}

std::vector<uint8_t> Protocolo::serializeUpdateAction(const std::vector<uint8_t> &data) {
    std::vector<uint8_t> result;
    //TODO: cambiar el UPDATE
    result.emplace_back(1);
    result.insert(result.end(),data.begin(),data.end());
    return result;
}

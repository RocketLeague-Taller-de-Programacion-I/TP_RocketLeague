//
// Created by lucaswaisten on 04/11/22.
//

#include "Action.h"
#include "protocolo.h"
#include "ActionCreate.h"
#include "ActionList.h"
#include "ActionJoin.h"
#include "ActionUpdate.h"

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
//    std::vector<uint8_t> result;
//    result.emplace_back(action->getType());
//    if (action->getType() == CREATE_ROOM) {
//        parseCreateRoomData(action, result);
//        return result;
//    } else if (action->getType() == MOVE) {
//        //insertar id del jugador previamente otorgado
//    }
//   // result.insert(result.end(), action.data.begin(), action.data.end());
//    return result;
    return action->beSerialized();
}

command_t Protocolo::getMapCommand(uint32_t action) {
    return this->mapCommand.at(action);
}

Action * Protocolo::deserializeData(const std::vector<uint8_t>& data) {
    uint8_t type(data[0]);

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
 * [1] -> players
 * [2] -> name
 *
 */
Action* Protocolo::parseCreateAction(const std::vector<uint8_t> &data) {
    uint8_t id(data[1]);
    uint8_t capacity(data[2]);
    std::string name(data.begin()+3,data.end());
//    std::shared_ptr<Action> pAction = std::make_shared<ActionCreate>(id, capacity, name);
//    std::unique_ptr<Action> pAction(new ActionCreate(id, capacity, std::move(name)));
    // create pointer to derived class and store into pointer of base class
    Action* pAction = new ActionCreate(id, capacity, std::move(name));
    return pAction;
}

Action * Protocolo::parseJoinAction(const std::vector<uint8_t> &data) {
    uint8_t id(data[0]);
    std::string name(data.begin()+1,data.end());
    //strip last spaces from name
    std::string stripped = name.substr(0, name.find_last_of(' '));
//    std::shared_ptr<Action> pAction = std::make_shared<ActionJoin>(id,name);
//    std::unique_ptr<Action> pAction(new ActionJoin(id, name));
    // create pointer to derived class and store into pointer of base class
    Action* pAction = new ActionJoin(id, stripped);
    return pAction;
}

Action * Protocolo::parseListAction(const std::vector<uint8_t> &data) {
//    std::shared_ptr<Action> pAction = std::make_shared<ActionList>(0);
//    std::unique_ptr<Action> pAction(new ActionList(0));
    // create pointer to derived class and store into pointer of base class
    Action* pAction = new ActionList(0);
    return pAction;
}

Action * Protocolo::parseUpdateAction(const std::vector<uint8_t> &vector) {
    uint8_t id(vector[1]);
    std::string data;
    if (not vector.empty()) {
        data = std::string(vector.begin()+2,vector.end());
    } else {
        data = "";
    }
//    std::shared_ptr<Action> pAction = std::make_shared<ActionUpdate>(id, name);
//    std::unique_ptr<Action> pAction(new ActionUpdate(id, name));
    // create pointer to derived class and store into pointer of base class
    Action* pAction = new ActionUpdate(id, data);
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
    result.emplace_back(UPDATE);
    result.insert(result.end(),data.begin(),data.end());
    return result;
}

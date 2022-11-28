//
// Created by lucaswaisten on 04/11/22.
//

#include "ServerProtocolo.h"

ServerAction * Protocolo::deserializeData(const uint8_t &id, const uint8_t &type,
                                          const std::function<void(std::vector<uint8_t> &, uint8_t &)> &receiveBytes) {
    switch (type) {
        case CREATE_ROOM:
            return parseCreateAction(id, receiveBytes);
        case JOIN_ROOM:
            return parseJoinAction(id, receiveBytes);
        case LIST_ROOMS:
            return parseListAction(id);
        case MOVE:
            return parseMoveAction(id, receiveBytes);
    }
    return {};
}

ServerAction * Protocolo::parseCreateAction(const uint8_t &id, const std::function<void(std::vector<uint8_t> &,uint8_t &)> &receiveBytes) {

    std::vector<uint8_t> capacity_and_nameSize(2);
    uint8_t size = capacity_and_nameSize.size();
    receiveBytes(capacity_and_nameSize, size);
    uint8_t capacity = capacity_and_nameSize[0];
    uint8_t nameSize = capacity_and_nameSize[1];

    std::vector<uint8_t> name(nameSize);
    size = name.size();
    receiveBytes(name, size);
    std::string nameString(name.begin(), name.end());

//    Action* pAction = new ActionCreate(id, capacity, name);
    ServerAction* pAction = new ServerCreateRoom(id, capacity, nameString);
    return pAction;
}

ServerAction * Protocolo::parseJoinAction(const uint8_t &id, const std::function<void(std::vector<uint8_t> &,
                                                                                      uint8_t &)> &receiveBytes) {
    std::vector<uint8_t> nameSize(1);
    uint8_t size = nameSize.size();
    receiveBytes(nameSize, size);

    std::vector<uint8_t> name(nameSize[0]);
    size = name.size();
    receiveBytes(name, size);
    std::string nameString(name.begin(), name.end());

    ServerAction* pAction = new ServerJoinRoom(id, nameString);
    return pAction;
}

ServerAction* Protocolo::parseListAction(const uint8_t &id) {
    ServerAction* pAction = new ServerListRooms(id);
    return pAction;
}

ServerAction *Protocolo::parseMoveAction(const uint8_t &id, const std::function<void(std::vector<uint8_t> &, uint8_t &)> &receiveBytes) {
    std::vector<uint8_t> direction_and_state(2);
    uint8_t size = direction_and_state.size();
    receiveBytes(direction_and_state, size);

    ServerAction* pAction = new ServerActionMove(id, direction_and_state[0], direction_and_state[1]);
    return pAction;
}

std::vector<uint8_t> Protocolo::serializeUpdateWorld(std::vector<int> &data) {
    uint16_t bx = data[0];
    sendBytes();
    uint16_t by = data[1];
}


//
// Created by roby on 22/11/22.
//

#include "ActionCreateRoom.h"

ActionCreateRoom::ActionCreateRoom(uint8_t &capacity, const std::string &name) : capacity(capacity), name(name){
    type = CREATE;
//    setDataVector*()
}

std::string ActionCreateRoom::getGameName() {
    return name;
}
uint8_t ActionCreateRoom::getCapacity() {
    return capacity;
}

uint8_t ActionCreateRoom::getType() const {
    return type;
}

std::vector<uint8_t> ActionCreateRoom::beSerialized() {
    // create a string from the name and the capacity
//    std::string nameCapacity = std::to_string(capacityGame) + nameGame;
    std::vector<uint8_t> createData;
    createData.push_back(type);
    createData.push_back(capacity);
    createData.push_back(name.length());
    createData.insert(createData.end(), name.begin(), name.end());
    return createData;
//    std::vector<uint8_t> createData(nameCapacity.begin(), nameCapacity.end());
//    return Protocolo::serializeCreateAction(createData);
}

ActionCreateRoom::~ActionCreateRoom() = default;

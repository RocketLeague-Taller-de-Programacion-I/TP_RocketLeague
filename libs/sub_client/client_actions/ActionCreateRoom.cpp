//
// Created by roby on 22/11/22.
//

#include "ActionCreateRoom.h"
#include "sub_client/ClientProtocol.h"
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

void ActionCreateRoom::beSerialized(ClientProtocol *protocolo) {
    protocolo->serializeCreateRoom(this);
}

ActionCreateRoom::~ActionCreateRoom() = default;

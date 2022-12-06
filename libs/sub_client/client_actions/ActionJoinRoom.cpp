//
// Created by roby on 22/11/22.
//

#include "ActionJoinRoom.h"
#include "sub_client/ClientProtocol.h"

ActionJoinRoom::ActionJoinRoom(std::string &roomName) : roomName(roomName){
    type = JOIN;
}

uint8_t ActionJoinRoom::getType() const {
    return type;
}

void ActionJoinRoom::beSerialized(ClientProtocol *protocolo) {
    protocolo->serializeJoinRoom(this);
}

std::string ActionJoinRoom::getRoomName() {
    return roomName;
}

ActionJoinRoom::~ActionJoinRoom() = default;


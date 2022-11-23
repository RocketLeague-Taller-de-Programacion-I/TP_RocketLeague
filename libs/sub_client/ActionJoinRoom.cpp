//
// Created by roby on 22/11/22.
//

#include "ActionJoinRoom.h"

ActionJoinRoom::ActionJoinRoom(std::string &roomName) : roomName(roomName){
    type = JOIN;
    serializeData();
}
void ActionJoinRoom::serializeData(){
    std::vector<uint8_t> joinData;
    joinData.push_back(type);
    joinData.insert(joinData.end(), roomName.begin(), roomName.end()); //append?
    data = joinData;
}
uint8_t ActionJoinRoom::getType() const {
    return type;
}

std::vector<uint8_t> ActionJoinRoom::beSerialized() {
    return data;
}

std::string ActionJoinRoom::getRoomName() {
    return roomName;
}

ActionJoinRoom::~ActionJoinRoom() = default;


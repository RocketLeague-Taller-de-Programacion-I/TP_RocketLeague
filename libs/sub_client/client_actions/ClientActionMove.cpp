//
// Created by roby on 27/11/22.
//

#include "ClientActionMove.h"

ClientActionMove::ClientActionMove(uint8_t direction, bool state) : direction(direction), state(state){
    type = MOVE;
}

std::vector<uint8_t> ClientActionMove::beSerialized() {
    std::vector<uint8_t> moveData;
    moveData.push_back(type);
    moveData.push_back(direction);
    moveData.push_back(state);
    return moveData;
}
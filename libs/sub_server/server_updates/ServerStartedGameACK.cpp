//
// Created by roby on 27/11/22.
//

#include "ServerStartedGameACK.h"

std::vector<uint8_t> ServerStartedGameACK::beSerialized() {
    std::vector<uint8_t> startedGameACKData;
    startedGameACKData.push_back(getType());
    startedGameACKData.push_back(id);
    startedGameACKData.push_back(returnCode);
    return startedGameACKData;
}

uint8_t ServerStartedGameACK::getType() const {
    return STARTED_GAME_ACK;
}

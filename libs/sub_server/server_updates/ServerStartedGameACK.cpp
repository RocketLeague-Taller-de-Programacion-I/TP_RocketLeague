//
// Created by roby on 27/11/22.
//

#include <functional>
#include "ServerStartedGameACK.h"

void ServerStartedGameACK::beSerialized(ServerProtocolo *protocolo,
                                        std::function<void(void *, unsigned int)> &sendCallable) {
//    std::vector<uint16_t> startedGameACKData;
//    startedGameACKData.push_back(htons(getType()));
//    startedGameACKData.push_back(htons(id));
//    startedGameACKData.push_back(htons(returnCode));
//    return startedGameACKData;
}

uint8_t ServerStartedGameACK::getType() const {
    return STARTED_GAME_ACK;
}

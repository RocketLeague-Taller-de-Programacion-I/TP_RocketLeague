//
// Created by roby on 24/11/22.
//

#include "ServerJoinACK.h"
#include "sub_server/ServerProtocolo.h"

std::vector<uint16_t> ServerJoinACK::beSerialized() {
    std::vector<uint16_t> joinACKData;
    joinACKData.push_back(htons(getType()));
    joinACKData.push_back(htons(id));
    joinACKData.push_back(htons(returnCode));
    return joinACKData;
}

uint16_t ServerJoinACK::getType() const {
    return JOIN_ACK;
}

//
// Created by roby on 24/11/22.
//

#include "ServerJoinACK.h"
#include "sub_server/ServerProtocolo.h"

std::vector<uint8_t> ServerJoinACK::beSerialized() {
    std::vector<uint8_t> joinACKData;
    joinACKData.push_back(getType());
    joinACKData.push_back(id);
    joinACKData.push_back(returnCode);
    return joinACKData;
}

uint8_t ServerJoinACK::getType() const {
    return JOIN_ACK;
}

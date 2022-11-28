//
// Created by roby on 24/11/22.
//

#include "ServerCreateACK.h"
#include "sub_server/ServerProtocolo.h" //TODO: change protocolo

std::vector<uint16_t> ServerCreateACK::beSerialized() {
    std::vector<uint16_t> createACKData;
    createACKData.push_back(htons(getType()));
    createACKData.push_back(htons(id));
    createACKData.push_back(htons(returnCode));
    return createACKData;
}

uint16_t ServerCreateACK::getType() const {
    return CREATE_ACK;
}


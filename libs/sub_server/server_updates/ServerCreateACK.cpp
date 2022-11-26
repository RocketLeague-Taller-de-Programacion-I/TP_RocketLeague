//
// Created by roby on 24/11/22.
//

#include "ServerCreateACK.h"
#include "sub_server/protocolo.h" //TODO: change protocolo

std::vector<uint8_t> ServerCreateACK::beSerialized() {
    std::vector<uint8_t> createACKData;
    createACKData.push_back(getType());
    createACKData.push_back(id);
    createACKData.insert(createACKData.end(), returnData.begin(), returnData.end());
    return createACKData;
}

uint8_t ServerCreateACK::getType() const {
    return CREATE_ACK;
}

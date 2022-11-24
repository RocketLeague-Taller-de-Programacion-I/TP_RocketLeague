//
// Created by roby on 24/11/22.
//

#include "ServerListACK.h"
#include "sub_server/protocolo.h"

std::vector<uint8_t> ServerListACK::beSerialized() {
    std::vector<uint8_t> listACKData;
    listACKData.push_back(getType());
    listACKData.push_back(id);
    listACKData.insert(listACKData.end(), returnData.begin(), returnData.end());
    return listACKData;
}

uint8_t ServerListACK::getType() const {
    return LIST_INFO;
}

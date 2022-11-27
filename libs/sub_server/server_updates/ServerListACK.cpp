//
// Created by roby on 24/11/22.
//

#include "ServerListACK.h"
#include "sub_server/ServerProtocolo.h"

std::vector<uint8_t> ServerListACK::beSerialized() {
    //[id,returnCode, cantidadDeGames,{online,max,sieName,name},...]
    std::vector<uint8_t> listACKData;
    listACKData.push_back(getType());
    listACKData.push_back(id);
    listACKData.push_back(returnCode);
    listACKData.push_back(numberOfGames);
    //data: online,max,sizeName,name
    listACKData.insert(listACKData.end(), returnData.begin(), returnData.end());
    return listACKData;
}

uint8_t ServerListACK::getType() const {
    return LIST_INFO;
}

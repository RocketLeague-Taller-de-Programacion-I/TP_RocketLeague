//
// Created by roby on 24/11/22.
//


#include "ServerListACK.h"
#include "sub_server/ServerProtocolo.h"

void ServerListACK::beSerialized(Protocolo *protocolo) {
//    //[id,returnCode, cantidadDeGames,{online,max,sieName,name},...]
//    std::vector<uint16_t> listACKData;
//    listACKData.push_back(htons(getType()));
//    listACKData.push_back(htons(id));
//    listACKData.push_back(htons(returnCode));
//    listACKData.push_back(htons(numberOfGames));
//    //data: online,max,sizeName,name
//    listACKData.insert(listACKData.end(), returnData.begin(), returnData.end());
//    return listACKData;
    protocolo->serializeServerListACK(this);
}

uint8_t ServerListACK::getType() const {
    return LIST_INFO;
}

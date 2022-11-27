//
// Created by roby on 24/11/22.
//

#include <map>
#include "ClientListACK.h"

ClientListACK::ClientListACK(uint8_t &id, uint8_t &returnCode, std::map<std::string, std::string> &listMap) :
    ClientUpdate(id, returnCode),
    listData(listMap){}

// TODO: a mejorar que devuelve, capaz un map?
std::map<std::string, std::string> ClientListACK::getList() {
    return listData;
}

ClientListACK::ClientListACK(uint8_t &id, uint8_t &returnCode) : ClientUpdate(id,returnCode) {
    listData = std::map<std::string,std::string>();
}

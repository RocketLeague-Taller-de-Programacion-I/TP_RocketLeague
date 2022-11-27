//
// Created by roby on 24/11/22.
//

#include "ClientListACK.h"

ClientListACK::ClientListACK(uint8_t &id, uint8_t &returnCode, std::vector<std::string> &list) :
    ClientUpdate(id, returnCode),
    listData(list){}

// TODO: a mejorar que devuelve, capaz un map?
std::vector<std::string> ClientListACK::getList() {
    return listData;
}

ClientListACK::ClientListACK(uint8_t &id, uint8_t &returnCode) : ClientUpdate(id,returnCode) {
    listData = std::vector<std::string>();
}

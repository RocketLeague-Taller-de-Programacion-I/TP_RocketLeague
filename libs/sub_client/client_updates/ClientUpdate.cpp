//
// Created by roby on 22/11/22.
//

#include "ClientUpdate.h"

//GameUpdate::GameUpdate(std::vector<uint8_t>& data) : data(data){}

ClientUpdate::ClientUpdate(uint8_t &id, std::string &returnCode) : id(id), data(returnCode){}


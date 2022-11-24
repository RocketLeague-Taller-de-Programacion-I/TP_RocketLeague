//
// Created by roby on 22/11/22.
//

#include "GameUpdate.h"

//GameUpdate::GameUpdate(std::vector<uint8_t>& data) : data(data){}

GameUpdate::GameUpdate(uint8_t &id, std::string &returnCode) : id(id), data(returnCode){}


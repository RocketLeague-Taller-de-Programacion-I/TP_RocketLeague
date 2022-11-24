//
// Created by roby on 22/11/22.
//

#include "GameUpdate.h"

GameUpdate::GameUpdate(std::vector<uint8_t>& data) : data(data){}

std::string GameUpdate:: getList() {
//    data {nombre,online,total,nombre,online,total}
    return std::string(data.begin(), data.end());
}

uint8_t GameUpdate::getId() {
    return data[0];
}

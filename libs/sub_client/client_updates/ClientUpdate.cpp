//
// Created by roby on 22/11/22.
//

#include "ClientUpdate.h"

Ball ClientUpdate::getBall() {
    return Ball(0, 0);
}

Score ClientUpdate::getScore() {
    return Score();
}

GameTime ClientUpdate::getTime() {
    return GameTime();
}

std::vector<Car> ClientUpdate::getCars() {
    return std::vector<Car>();
}

std::map<std::string, std::string> ClientUpdate::getList() {
    return std::map<std::string, std::string>();
}

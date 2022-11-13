//
// Created by roby on 12/11/22.
//

#include "Action.h"

Action::Action(const uint8_t &type, std::vector<uint8_t> &data) : type(type), data(data) {}

std::uint8_t Action::getType() const {
    return type;
}

Action::Action(const uint8_t &type, std::string &data)
    : type(type)
    , data(data.begin(), data.end()) {}

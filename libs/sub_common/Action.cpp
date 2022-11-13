//
// Created by roby on 12/11/22.
//

#include <vector>
#include "Action.h"

Action::Action(const uint8_t &type, std::vector<char> &data) : type(type), data(data) {}

std::uint8_t Action::getType() const {
    return type;
}
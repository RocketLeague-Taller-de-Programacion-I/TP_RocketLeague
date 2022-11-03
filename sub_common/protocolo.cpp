//
// Created by lucaswaisten on 01/11/22.
//

#include <sstream>
#include "protocolo.h"

uint8_t Protocolo::serializeAction(const std::string &action) {
    return this->mapCommand.at(action);
}

command_t Protocolo::serializeMenuAction(const std::string &menuAction) {
    return this->mapMenuCommand.at(menuAction);
}

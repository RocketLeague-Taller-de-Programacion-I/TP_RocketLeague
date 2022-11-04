//
// Created by lucaswaisten on 04/11/22.
//

#include "protocolo.h"

command_t Protocolo::serializeAction(const std::string &action) {
    return this->mapCommand.at(action);
}

//
// Created by lucaswaisten on 04/11/22.
//

#include "protocolo.h"

command_t Protocolo::serializeAction(uint32_t action) {
    return this->mapCommand.at(action);
}

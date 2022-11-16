//
// Created by lucaswaisten on 16/11/22.
//

#include "ActionCreate.h"

#include <utility>

ActionCreate::ActionCreate(uint8_t id, uint8_t c, std::string name) : Action(id,c,std::move(name)) {}

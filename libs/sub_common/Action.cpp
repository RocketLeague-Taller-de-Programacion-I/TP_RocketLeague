//
// Created by lucaswaisten on 12/11/22.
//

#include "Action.h"

Action::Action() : idInvoker(0) {}

Action::Action(uint8_t &id) : idInvoker(id) {}

uint8_t Action::getId() {
    return 0;
}

void Action::execute() {}

std::vector<uint8_t> Action::beSerialized() {
    return std::vector<uint8_t>();
}

Action::~Action() = default;



//
// Created by franco on 22/11/22.
//

#include "ActionCreate.h"
#include "../protocolo.h"

ActionCreate::ActionCreate(uint8_t &id, uint8_t &players, std::string &name) : Action(id), players(players), gameName(name) { }

uint8_t ActionCreate::getId() {
    return this->idInvoker;
}

std::vector<uint8_t> ActionCreate::beSerialized() {
    // create a string from the name and the capacity
    std::string nameCapacity = std::to_string(players) + gameName;
    std::vector<uint8_t> createData(nameCapacity.begin(), nameCapacity.end());
    return Protocolo::serializeCreateAction(createData);
}

ActionCreate::~ActionCreate() = default;




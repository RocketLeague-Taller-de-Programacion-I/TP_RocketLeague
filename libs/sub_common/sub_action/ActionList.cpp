//
// Created by franco on 22/11/22.
//

#include "ActionList.h"
#include "sub_common/protocolo.h"

ActionList::ActionList(uint8_t &id) : Action(id) {}

ActionList::~ActionList() {}

uint8_t ActionList::getId() {
    return this->idInvoker;
}

std::vector<uint8_t> ActionList::beSerialized() {
    std::vector<uint8_t> dummyData;
    return Protocolo::serializeListAction(dummyData);
}
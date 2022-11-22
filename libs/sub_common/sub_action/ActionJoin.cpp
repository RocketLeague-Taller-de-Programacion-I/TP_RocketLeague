//
// Created by franco on 22/11/22.
//

#include "ActionJoin.h"
#include "sub_common/protocolo.h"

ActionJoin::ActionJoin(uint8_t &id, std::string &name) : Action(id), gameName(name) { }

uint8_t ActionJoin::getId() {
    return this->idInvoker;
}

std::vector<uint8_t> ActionJoin::beSerialized() {
    std::vector<uint8_t> joinData(this->getGameName().begin(), this->getGameName().end());
    return Protocolo::serializeJoinAction(joinData);
}

ActionJoin::~ActionJoin() {

}
std::string ActionJoin::getGameName() {
    return this->gameName;
}

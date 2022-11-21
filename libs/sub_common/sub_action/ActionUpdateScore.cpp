//
// Created by franco on 21/11/22.
//

#include "ActionUpdateScore.h"
ActionUpdateScore::ActionUpdateScore(uint8_t & id, int &local, int &visit) : ActionUpdate(id, (std::string &) ""), local(local), visit(visit) {
}
ActionUpdateScore::~ActionUpdateScore() {}

int ActionUpdateScore::getLocal() {
    return this->local;
}
int ActionUpdateScore::getVisit() {
    return this->visit;
}
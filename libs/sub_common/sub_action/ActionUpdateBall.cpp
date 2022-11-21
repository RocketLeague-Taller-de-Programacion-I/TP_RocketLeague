//
// Created by franco on 21/11/22.
//

#include "ActionUpdateBall.h"

ActionUpdateBall::ActionUpdateBall(uint8_t &id, int &posX, int &posY) : ActionUpdate(id,(std::string &) ""), x(posX), y(posY){}


ActionUpdateBall::~ActionUpdateBall() {
}
int ActionUpdateBall::getX() const {
    return this->x;
}
int ActionUpdateBall::getY() const {
    return this->y;
}
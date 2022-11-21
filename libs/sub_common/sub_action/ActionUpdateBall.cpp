//
// Created by franco on 21/11/22.
//

#include "ActionUpdateBall.h"

ActionUpdateBall::ActionUpdateBall(uint8_t &id, float &posX, float &posY, float &angle) : ActionUpdate(id,
                                                                                                       (std::string &) ""){}


ActionUpdateBall::~ActionUpdateBall() {
}
float ActionUpdateBall::getX() const {
    return this->x;
}
float ActionUpdateBall::getY() const {
    return this->y;
}
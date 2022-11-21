//
// Created by franco on 21/11/22.
//

#include "ActionUpdateCar.h"

ActionUpdateCar::ActionUpdateCar(uint8_t &id, float &posX, float &posY, float &angle) : ActionUpdate(id,
                                                                                                     (std::string &) ""), x(posX), y(posY), angle(angle){

}
ActionUpdateCar::~ActionUpdateCar() { }
float ActionUpdateCar::getX() const {
    return this->x;
}
float ActionUpdateCar::getY() const {
    return this->y;
}
float ActionUpdateCar::getAngle() const {
    return this->angle;
}
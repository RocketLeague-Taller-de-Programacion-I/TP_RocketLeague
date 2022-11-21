//
// Created by franco on 21/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONUPDATECAR_H
#define ROCKETLEAGUE_ACTIONUPDATECAR_H
#include "ActionUpdate.h"

class ActionUpdateCar : public ActionUpdate {
public:
    ActionUpdateCar(uint8_t &id, float &posX, float &posY, float &angle);
    ~ActionUpdateCar() override;
    float getY() const;
    float getX() const;
    float getAngle() const;
private:
    float x;  //  pixeles
    float y;
    float angle;  //  deg
};


#endif //ROCKETLEAGUE_ACTIONUPDATECAR_H

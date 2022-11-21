//
// Created by franco on 21/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONUPDATEBALL_H
#define ROCKETLEAGUE_ACTIONUPDATEBALL_H
#include "ActionUpdate.h"

class ActionUpdateBall : public ActionUpdate {
public:
    ActionUpdateBall(uint8_t &id, float &posX, float &posY, float &angle);
    float getY() const;
    float getX() const;
    ~ActionUpdateBall() override;
private:
    float x;  //  pixel
    float y;  //  pixel
    float angle;  //  deg
};


#endif //ROCKETLEAGUE_ACTIONUPDATEBALL_H

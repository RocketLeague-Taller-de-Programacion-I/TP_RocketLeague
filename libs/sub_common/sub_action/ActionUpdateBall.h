//
// Created by franco on 21/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONUPDATEBALL_H
#define ROCKETLEAGUE_ACTIONUPDATEBALL_H
#include "ActionUpdate.h"

class ActionUpdateBall : public ActionUpdate {
public:
    ActionUpdateBall(uint8_t &id, int &posX, int &posY);
    int getY() const;
    int getX() const;
    ~ActionUpdateBall() override;
private:
    int x;  //  pixel
    int y;  //  pixel
};


#endif //ROCKETLEAGUE_ACTIONUPDATEBALL_H

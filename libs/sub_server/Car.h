//
// Created by franco on 07/11/22.
//

#ifndef ROCKETLEAGUE_CAR_H
#define ROCKETLEAGUE_CAR_H
#include "box2d/b2_body.h"
#include "box2d/box2d.h"
#include <iostream>

class Car {
    std::string playerName;
    bool turboOn;
    b2Body *m_car;
    b2BodyDef bd;
    b2PolygonShape chassis;
    b2Fixture* fixture;
public:
    explicit Car(b2World* world);
    ~Car();
    void goRight();
    void goLeft();
    void stop();
    void jump();
    void turbo();
    void check_y_pos();
    std::string name();
    int GetPosition();
};


#endif //ROCKETLEAGUE_CAR_H

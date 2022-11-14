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
    b2FixtureDef fd;
    b2BodyDef bd;
    b2PolygonShape chassis;
    b2WheelJoint *m_spring1;
    b2WheelJoint *m_spring2;
    b2Body * m_wheel1;
    b2Body * m_wheel2;
    float m_speed = 50.0f;
    int remainingJumpSteps;
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
};


#endif //ROCKETLEAGUE_CAR_H

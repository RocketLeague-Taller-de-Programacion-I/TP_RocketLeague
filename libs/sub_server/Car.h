//
// Created by franco on 07/11/22.
//

#ifndef ROCKETLEAGUE_CAR_H
#define ROCKETLEAGUE_CAR_H
#include "box2d/b2_body.h"
#include "box2d/box2d.h"

class Car {
    b2WheelJoint *m_spring1;
    b2WheelJoint *m_spring2;
    float m_speed = 50.0f;
public:
    Car(b2World* world);
    ~Car();

    void goRight();
    void goLeft();

    void stop();
};


#endif //ROCKETLEAGUE_CAR_H

//
// Created by franco on 07/11/22.
//

#ifndef ROCKETLEAGUE_BALL_H
#define ROCKETLEAGUE_BALL_H


#include "box2d/b2_body.h"

class Ball {
public:
    //class member variables
    b2Body* m_body;
    float m_radius;

public:
    Ball(b2World* world, float radius);
    ~Ball();

};



#endif //ROCKETLEAGUE_BALL_H

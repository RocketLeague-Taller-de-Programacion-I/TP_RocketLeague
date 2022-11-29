//
// Created by franco on 07/11/22.
//

#ifndef ROCKETLEAGUE_BALL_H
#define ROCKETLEAGUE_BALL_H


#include <memory>
#include "box2d/b2_body.h"
#include "box2d/box2d.h"
#include "Car.h"

class Ball {
public:
    //class member variables
    b2Body* m_body;
    b2Fixture* ballFixture;
    b2FixtureDef fixDef;
    b2BodyDef myBodyDef;
    std::unique_ptr<MyFixtureUserDataType> myUserData;
    float m_radius;

public:
    Ball(b2World* world, float radius);
    ~Ball();
    float X() const;
    float Y() const;

    void restartGame() const;
};



#endif //ROCKETLEAGUE_BALL_H
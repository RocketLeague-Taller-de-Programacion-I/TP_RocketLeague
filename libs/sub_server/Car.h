//
// Created by franco on 07/11/22.
//

#ifndef ROCKETLEAGUE_CAR_H
#define ROCKETLEAGUE_CAR_H
#include "box2d/b2_body.h"
#include "box2d/box2d.h"
#include <iostream>
#include <memory>

struct MyFixtureUserDataType
{
    int mObjectType {};
    b2Fixture* mOwningFixture {};
};
class Car {
    uint8_t id;
    std::string playerName;
    bool turboOn;
    b2Body *m_car;
    b2BodyDef bd;
    b2PolygonShape chassis;
    b2FixtureDef fixDef;
    std::unique_ptr<MyFixtureUserDataType> myUserData;
public:
    explicit Car(b2World* world, uint8_t& id);
    ~Car();
    void goRight();
    void goLeft();
    void stop();
    void jump();
    void turbo();
    void check_y_pos();
    int X();
    int Y();
    float angle();
    int angleDeg();
    uint8_t getId();
};


#endif //ROCKETLEAGUE_CAR_H
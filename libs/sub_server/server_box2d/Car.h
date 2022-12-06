//
// Created by franco on 07/11/22.
//

#ifndef ROCKETLEAGUE_CAR_H
#define ROCKETLEAGUE_CAR_H
#include "box2d/b2_body.h"
#include "box2d/box2d.h"
#include <iostream>
#include <memory>
class Car;
struct MyFixtureUserDataType
{
    int mObjectType {};
    b2Fixture* mOwningFixture {};
    bool* facingRight;
    uint8_t id;
};
class Car {
    uint8_t id;
    std::string playerName;
    bool turboOn;
    bool movingLeft;
    bool movingRight;
    bool facingRight;
    b2Body *m_car;
    b2BodyDef bd;
    b2PolygonShape chassis;
    b2FixtureDef fixDef;
    std::unique_ptr<MyFixtureUserDataType> myUserData;
    std::unique_ptr<MyFixtureUserDataType> userDataDown;
    std::unique_ptr<MyFixtureUserDataType> userDataLeft;
    std::unique_ptr<MyFixtureUserDataType> userDataRight;
    std::unique_ptr<MyFixtureUserDataType> userDataUp;
public:
    explicit Car(b2World* world, uint8_t& id);
    ~Car();
    void goRight();
    void goLeft();
    void jump();
    void turbo();
    void check_y_pos();
    float X();
    float Y();
    float angle();
    float angleDeg();
    uint8_t getId();
    void startMovingRight();
    void startMovingLeft();
    void stopMovingRight();
    void stopMovingLeft();
    void update();
    bool facingWhere();

    uint8_t carId();
};


#endif //ROCKETLEAGUE_CAR_H
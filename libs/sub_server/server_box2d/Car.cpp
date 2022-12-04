//
// Created by franco on 07/11/22.
//

#include <memory>
#include "Car.h"
#include "box2d/box2d.h"
#define RADTODEG 57.2958
#define BALL 0x0002
#define CAR -3
#define GROUND 0x0004


Car::Car(b2World* world, uint8_t& id) : id(id), turboOn(false), movingLeft(false), movingRight(false), facingRight(true) {
    b2Vec2 vertices[8];
    /*
    vertices[0].Set(-1.5f, -0.5f);
    vertices[1].Set(1.5f, -0.5f);
    vertices[2].Set(1.5f, 0.0f);
    vertices[3].Set(0.0f, 0.9f);
    vertices[4].Set(-1.15f, 0.9f);
    vertices[5].Set(-1.5f, 0.2f);
    */
    vertices[0].Set(-1.5f, -.25f);
    vertices[1].Set(1.5f, -.25f);
    vertices[2].Set(-1.5f, 1.f);
    vertices[3].Set(1.5f, 1.f);

    myUserData = std::make_unique<MyFixtureUserDataType>();
    fixDef.userData.pointer = reinterpret_cast<uintptr_t>(myUserData.get());
    myUserData->mObjectType = 3;
    chassis.Set(vertices, 4);
    bd.type = b2_dynamicBody;
    bd.position.Set(20.0f, 1.0f);
    fixDef.density = 1.f;
    fixDef.restitution = 0.3f;
    fixDef.shape = &chassis;
    fixDef.filter.groupIndex = CAR;
    m_car = world->CreateBody(&bd);
    myUserData->mOwningFixture =  m_car->CreateFixture(&fixDef);
    myUserData->mOwningFixture->SetFilterData(fixDef.filter);

    // Down sensor
    b2Vec2 vertDown[4];
    vertDown[0].Set(-1.25f, -.5f);
    vertDown[1].Set(1.25f,-.5f);
    vertDown[2].Set(-1.25f, .05f);
    vertDown[3].Set(1.25f, .05f);
    b2PolygonShape down;
    down.Set(vertDown, 4);
    b2FixtureDef fixDefDown;
    fixDefDown.density = 1.f;
    fixDefDown.restitution = 0.1f;
    fixDefDown.shape = &down;
    fixDefDown.filter.groupIndex = CAR;
    fixDefDown.isSensor = true;
    userDataDown = std::make_unique<MyFixtureUserDataType>();
    fixDefDown.userData.pointer = reinterpret_cast<uintptr_t>(userDataDown.get());
    userDataDown->mObjectType = 4;  //  Down
    userDataDown->mOwningFixture =  m_car->CreateFixture(&fixDefDown);
    userDataDown->mOwningFixture->SetFilterData(fixDefDown.filter);

    // Left sensor
    b2Vec2 vertLeft[4];
    vertLeft[0].Set(-1.75f, 0.f);
    vertLeft[1].Set(-1.25f,0.f);
    vertLeft[2].Set(-1.75f, .75f);
    vertLeft[3].Set(-1.25f, .75f);
    b2PolygonShape left;
    left.Set(vertLeft, 4);
    b2FixtureDef fixDefLeft;
    fixDefLeft.density = 1.f;
    fixDefLeft.restitution = 0.1f;
    fixDefLeft.shape = &left;
    fixDefLeft.filter.groupIndex = CAR;
    fixDefLeft.isSensor = true;
    userDataLeft = std::make_unique<MyFixtureUserDataType>();
    fixDefLeft.userData.pointer = reinterpret_cast<uintptr_t>(userDataLeft.get());
    userDataLeft->mObjectType = 5;  //  Left
    userDataLeft->mOwningFixture =  m_car->CreateFixture(&fixDefLeft);
    userDataLeft->mOwningFixture->SetFilterData(fixDefLeft.filter);

    // Right sensor
    b2Vec2 vertRight[4];
    vertRight[0].Set(1.25f, 0.f);
    vertRight[1].Set(1.75f,0.f);
    vertRight[2].Set(1.25f, .75f);
    vertRight[3].Set(1.75f, .75f);
    b2PolygonShape right;
    right.Set(vertRight, 4);
    b2FixtureDef fixDefRight;
    fixDefRight.density = 1.f;
    fixDefRight.restitution = 0.1f;
    fixDefRight.shape = &right;
    fixDefRight.filter.groupIndex = CAR;
    fixDefRight.isSensor = true;
    userDataRight = std::make_unique<MyFixtureUserDataType>();
    fixDefRight.userData.pointer = reinterpret_cast<uintptr_t>(userDataRight.get());
    userDataRight->mObjectType = 6;  //  Right
    userDataRight->mOwningFixture =  m_car->CreateFixture(&fixDefRight);
    userDataRight->mOwningFixture->SetFilterData(fixDefRight.filter);

    // Upper sensor
    b2Vec2 vertUp[4];
    vertUp[0].Set(-1.25f, .75f);
    vertUp[1].Set(1.25f,.75f);
    vertUp[2].Set(-1.25f, 1.15f);
    vertUp[3].Set(1.25f, 1.15f);
    b2PolygonShape up;
    up.Set(vertUp, 4);
    b2FixtureDef fixDefUp;
    fixDefUp.density = 1.f;
    fixDefUp.restitution = 0.3f;
    fixDefUp.shape = &up;
    fixDefUp.filter.groupIndex = CAR;
    fixDefUp.isSensor = true;
    userDataUp = std::make_unique<MyFixtureUserDataType>();
    fixDefUp.userData.pointer = reinterpret_cast<uintptr_t>(userDataUp.get());
    userDataUp->mObjectType = 7;  //  Up
    userDataUp->mOwningFixture =  m_car->CreateFixture(&fixDefUp);
    userDataUp->mOwningFixture->SetFilterData(fixDefUp.filter);
     }
void Car::goRight() {
    if (this->m_car->GetPosition().y > 4) {
        m_car->ApplyTorque(-100.0, true);
        return;
    }
    if (turboOn) {
        m_car->ApplyForce(b2Vec2(75, 0), m_car->GetWorldCenter(), true);
        turboOn = false;
        return;
    }
    //  ApplyForceToCenter
    m_car->ApplyForce(b2Vec2(50, 0), m_car->GetWorldCenter(), true);
}
//
void Car::goLeft() {
    if (this->m_car->GetPosition().y > 4) {
        m_car->ApplyTorque(100.0, true);
        return;
    }
    if (turboOn) {
        m_car->ApplyForce(b2Vec2(-75,0), m_car->GetWorldCenter(), true);
        turboOn = false;
        return;
    }
    m_car->ApplyForce(b2Vec2(-50, 0), m_car->GetWorldCenter(), true);
}
void Car::stop() {
    // fixture->SetFriction(100);
}

void Car::turbo() {
    this->turboOn = true;
}
void Car::jump() {
    check_y_pos();
}

Car::~Car() {
}

//  OK
void Car::check_y_pos() {
    if (Y() > 5) { return; }
    if (Y() > 3) {
        m_car->ApplyForce(b2Vec2(0, 3000), m_car->GetWorldCenter(), true);
        return;
    }
    m_car->ApplyForce(b2Vec2(0, 5000), m_car->GetWorldCenter(), true);
}
float Car::Y() {
    return this->m_car->GetPosition().y;
}
float Car::X() {
    return this->m_car->GetPosition().x;
}

float Car::angle() {
    return this->m_car->GetAngle();
}

float Car::angleDeg() {
    return (angle()*RADTODEG);
}

uint8_t Car::getId() {
    return this->id;
}
void Car::startMovingRight() {
    this->movingRight = true;
    this->facingRight = true;
    this->movingLeft = false;
}
void Car::startMovingLeft() {
    this->movingRight = false;
    this->facingRight = false;
    this->movingLeft = true;
}
void Car::stopMovingRight() {
    this->movingRight = false;
}
void Car::stopMovingLeft() {
    this->movingLeft = false;
}
void Car::update() {
    if (movingRight and X() < 38.0) {
        goRight();
    }
    if (movingLeft and X() > 1) {
        goLeft();
    }
    if(X() > 38.0) {
        this->m_car->SetTransform(b2Vec2(38.0, Y()), true);
        m_car->ApplyLinearImpulseToCenter(b2Vec2(-5,0), true);
    }
    if(X() < 0.5) {
        this->m_car->SetTransform(b2Vec2(0.5, Y()), true);
        m_car->ApplyLinearImpulseToCenter(b2Vec2(5,0), true);
    }
}
bool Car::facingWhere() {
    return this->facingRight;
}
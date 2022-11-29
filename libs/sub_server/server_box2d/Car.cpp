//
// Created by franco on 07/11/22.
//

#include <memory>
#include "Car.h"
#include "box2d/box2d.h"
#define RADTODEG 57.2958



Car::Car(b2World* world, uint8_t& id) : id(id), turboOn(false), movingLeft(false), movingRight(false) {
    b2Vec2 vertices[8];
    /*
    vertices[0].Set(-1.5f, -0.5f);
    vertices[1].Set(1.5f, -0.5f);
    vertices[2].Set(1.5f, 0.0f);
    vertices[3].Set(0.0f, 0.9f);
    vertices[4].Set(-1.15f, 0.9f);
    vertices[5].Set(-1.5f, 0.2f);
    */
    vertices[0].Set(-1.5f, -.5f);
    vertices[1].Set(1.5f, -.5f);
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
    m_car = world->CreateBody(&bd);
    myUserData->mOwningFixture =  m_car->CreateFixture(&fixDef);

}
void Car::goRight() {
    if (this->m_car->GetPosition().y > 4) {
        m_car->ApplyTorque(-500.0, true);
        return;
    }
    if (turboOn) {
        m_car->ApplyForce(b2Vec2(200, 0), m_car->GetWorldCenter(), true);
        turboOn = false;
        return;
    }
    //  ApplyForceToCenter
    m_car->ApplyForce(b2Vec2(120, 0), m_car->GetWorldCenter(), true);
}
//
void Car::goLeft() {
    if (this->m_car->GetPosition().y > 4) {
        m_car->ApplyTorque(500.0, true);
        return;
    }
    if (turboOn) {
        m_car->ApplyForce(b2Vec2(-200,0), m_car->GetWorldCenter(), true);
        turboOn = false;
        return;
    }
    m_car->ApplyForce(b2Vec2(-120, 0), m_car->GetWorldCenter(), true);
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
    if (Y() > 6) { return; }
    if (Y() > 3) {
        m_car->ApplyForce(b2Vec2(0, 120), m_car->GetWorldCenter(), true);
        return;
    }
    m_car->ApplyForce(b2Vec2(0, 200), m_car->GetWorldCenter(), true);
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
    this->movingLeft = false;
}
void Car::startMovingLeft() {
    this->movingRight = false;
    this->movingLeft = true;
}
void Car::stopMovingRight() {
    this->movingRight = false;
}
void Car::stopMovingLeft() {
    this->movingLeft = false;
}
void Car::update() {
    if (movingRight) {
        goRight();
    }
    if (movingLeft) {
        goLeft();
    }
}
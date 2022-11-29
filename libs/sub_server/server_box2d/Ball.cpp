//
// Created by franco on 07/11/22.
//

#include "Ball.h"
#include "box2d/box2d.h"

Ball::Ball(b2World* world, float radius) {
    myUserData = std::make_unique<MyFixtureUserDataType>();
    fixDef.userData.pointer = reinterpret_cast<uintptr_t>(myUserData.get());
    myUserData->mObjectType = 2;
    m_body = NULL;
    m_radius = radius;
    //set up dynamic body, store in class variable
    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(20, 10);
    m_body = world->CreateBody(&myBodyDef);
    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0);
    circleShape.m_radius = m_radius; //use class variable
    fixDef.shape = &circleShape;
    fixDef.density = 1;
    fixDef.restitution = 0.7;
    myUserData->mOwningFixture =  m_body->CreateFixture(&fixDef);
    this->ballFixture = myUserData->mOwningFixture;
}
float Ball::X() const {
    return (this->m_body->GetPosition().x);
}
float Ball::Y() const {
    return (this->m_body->GetPosition().y);
}
void Ball::restartGame() const {
    m_body->SetTransform(b2Vec2(20,10),m_body->GetAngle());
    m_body->ApplyLinearImpulseToCenter(b2Vec2(0,10), true);
}

Ball::~Ball() { }
#include "Ball.h"
#include "box2d/box2d.h"

#define BALL 0x0002
#define CAR (-3)
#define GROUND 0x0004
#define RADTODEG 57.2958

#define BALL_RESTITUTION 0.08

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
    fixDef.density = 0.5;
    fixDef.restitution = BALL_RESTITUTION;
    fixDef.filter.groupIndex = BALL;
    myUserData->mOwningFixture =  m_body->CreateFixture(&fixDef);
    myUserData->mOwningFixture->SetFilterData(fixDef.filter);
    this->ballFixture = myUserData->mOwningFixture;
}
float Ball::X() const {
    return (this->m_body->GetPosition().x);
}
float Ball::Y() const {
    return (this->m_body->GetPosition().y);
}
void Ball::restartGame() const {
    usleep(6000);
    m_body->SetTransform(b2Vec2(20,10),m_body->GetAngle());
}
float Ball::angleDeg() const {
    return (this->m_body->GetAngle()*RADTODEG);
}

Ball::~Ball() { }
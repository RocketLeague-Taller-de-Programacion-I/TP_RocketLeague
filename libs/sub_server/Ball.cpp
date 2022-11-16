//
// Created by franco on 07/11/22.
//

#include "Ball.h"
#include "box2d/box2d.h"

Ball::Ball(b2World* world, float radius) {
    m_body = NULL;
    m_radius = radius;
    //set up dynamic body, store in class variable
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(0, 20);
    m_body = world->CreateBody(&myBodyDef);
    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0);
    circleShape.m_radius = m_radius; //use class variable
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &circleShape;
    myFixtureDef.density = 1;
    myFixtureDef.restitution = 0.7;
    ballFixture = m_body->CreateFixture(&myFixtureDef);
}
float Ball::X() const {
    return(this->m_body->GetPosition().x);
}
float Ball::Y() const {
    return(this->m_body->GetPosition().y);
}

Ball::~Ball() { }
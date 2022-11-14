//
// Created by franco on 07/11/22.
//

#include "Car.h"
#include "box2d/box2d.h"
#define NO_VEL 0
#define DEGTORAD 0.0174533
#define cojstaxisY 0.35

Car::Car(b2World* world) : turboOn(false), remainingJumpSteps(0) {
    //  a
    b2Vec2 vertices[8]; //  a
    vertices[0].Set(-1.5f, -0.5f);
    vertices[1].Set(1.5f, -0.5f);
    vertices[2].Set(1.5f, 0.0f);
    vertices[3].Set(0.0f, 0.9f);
    vertices[4].Set(-1.15f, 0.9f);
    vertices[5].Set(-1.5f, 0.2f);
    chassis.Set(vertices, 6);

    b2CircleShape circle;
    circle.m_radius = 0.4f;


    bd.type = b2_dynamicBody;
    bd.position.Set(0.0f, 1.0f);
    m_car = world->CreateBody(&bd);
    m_car->CreateFixture(&chassis, 1.0f);


    fd.shape = &circle;
    fd.density = 1.0f;
    fd.friction = 0.9f;

    bd.position.Set(-1.0f, 0.35f);
    m_wheel1 = world->CreateBody(&bd);
    m_wheel1->CreateFixture(&fd);

    bd.position.Set(1.0f, 0.4f);
    m_wheel2 = world->CreateBody(&bd);
    m_wheel2->CreateFixture(&fd);

    b2WheelJointDef jd;
    b2Vec2 axis(0.0f, 1.0f);

    float mass1 = m_wheel1->GetMass();
    float mass2 = m_wheel2->GetMass();

    float hertz = 4.0f;
    float dampingRatio = 0.7f;
    float omega = 2.0f * b2_pi * hertz;

    jd.Initialize(m_car, m_wheel1, m_wheel1->GetPosition(), axis);
    jd.motorSpeed = 0.0f;
    jd.maxMotorTorque = 1000.0f;
    jd.enableMotor = true;
    jd.stiffness = mass1 * omega * omega;
    jd.damping = 2.0f * mass1 * dampingRatio * omega;
    jd.lowerTranslation = -0.25f;
    jd.upperTranslation = 0.25f;
    jd.enableLimit = true;
    m_spring1 = (b2WheelJoint *) world->CreateJoint(&jd);

    jd.Initialize(m_car, m_wheel2, m_wheel2->GetPosition(), axis);
    jd.motorSpeed = 0.0f;
    jd.maxMotorTorque = 1000.0f;
    jd.enableMotor = false; //  No se mueve la rueda delantera
    jd.stiffness = mass2 * omega * omega;
    jd.damping = 2.0f * mass2 * dampingRatio * omega;
    jd.lowerTranslation = -0.25f;
    jd.upperTranslation = 0.25f;
    jd.enableLimit = true;
    (b2WheelJoint *) world->CreateJoint(&jd);

}
void Car::goRight() {
    //  Ruedas giran horario
    if (turboOn) {
        this->m_car->SetLinearVelocity(b2Vec2(20, this->m_car->GetLinearVelocity().y));
        turboOn = false;
        return;
    }
    this->m_car->SetLinearVelocity(b2Vec2(5, this->m_car->GetLinearVelocity().y));

}
void Car::goLeft() {
    if (turboOn) {
        this->m_car->SetLinearVelocity(b2Vec2(-20, this->m_car->GetLinearVelocity().y));
        turboOn = false;
        return;
    }
    this->m_car->SetLinearVelocity(b2Vec2(-5, this->m_car->GetLinearVelocity().y));
}
void Car::stop()
{
    //  Ruedas giran antihrario
    this->m_spring1->SetMotorSpeed(NO_VEL);
}

void Car::turbo() {
    this->turboOn = true;
}
void Car::jump() {

    // 1/10th of a second at 60H
    check_y_pos();
    remainingJumpSteps += 6;
}

Car::~Car() = default;

void Car::check_y_pos() {
    if (remainingJumpSteps >= 0) {
        //to change velocity by 10 in one time step
        float force = m_car->GetMass() * 50 / (1 / 60.0); //f = mv/t
        //spread this over 6 time steps
        force /= 6.0;
        m_car->ApplyForce(b2Vec2(0, force), m_car->GetWorldCenter(), true);
        remainingJumpSteps--;
        return;
    }
    //to change velocity by 10 in one time step
    float force = m_car->GetMass() * 50 / (1 / 60.0); //f = mv/t
    //spread this over 6 time steps
    force /= 6.0;
    m_car->ApplyForce(b2Vec2(0, force), m_car->GetWorldCenter(), true);
    remainingJumpSteps--;
}
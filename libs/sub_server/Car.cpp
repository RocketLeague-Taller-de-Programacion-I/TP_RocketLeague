//
// Created by franco on 07/11/22.
//

#include "Car.h"
#include "box2d/box2d.h"
#define NO_VEL 0
#define DEGTORAD 0.0174533

Car::Car(b2World* world) : remainingJumpSteps(0), turboOn(false) {
    b2PolygonShape chassis; //  a
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
    if (remainingJumpSteps > 6) {
    float bodyAngle = m_car->GetAngle();
    m_car->SetAngularVelocity(0);
    float totalRotation = 360;
    float change = 6 * DEGTORAD;  //allow 1 degree rotation per time step
    float newAngle = bodyAngle + fmin(change, fmax(-change, totalRotation));
    m_car->SetTransform(m_car->GetPosition(), newAngle);
    }
    this->m_spring1->SetMotorSpeed(-m_speed);
    if (this->turboOn){
        this->m_spring1->SetMotorSpeed(-1000*m_speed);
        this->turboOn = false;
    }

}
void Car::goLeft()
{
    //  Ruedas giran antihrario
    if (this->turboOn) {
        this->m_spring1->SetMotorSpeed(-5*m_speed);
        this->turboOn = false;
        return;
    }
    this->m_spring1->SetMotorSpeed(m_speed);
    if (remainingJumpSteps > 6) {
        float bodyAngle = m_car->GetAngle();
        b2Vec2 toTarget = b2Vec2(0,0) - m_car->GetPosition();
        float desiredAngle = atan2f( -toTarget.x, toTarget.y );
        m_car->SetAngularVelocity(0);
        //m_car->SetTransform( m_car->GetPosition(), desiredAngle );
        float totalRotation = 360;
        float change = 6 * DEGTORAD;  //allow 1 degree rotation per time step
        float newAngle = bodyAngle + fmin( change, fmax(-change, totalRotation));
        m_car->SetTransform( m_car->GetPosition(), newAngle );
    }

}
void Car::stop()
{
    //  Ruedas giran antihrario
    this->m_spring1->SetMotorSpeed(NO_VEL);
}
void Car::jump() {
    remainingJumpSteps += 6;
    // 1/10th of a second at 60H
    check_y_pos();
}
void Car::turbo() {
    this->turboOn = true;
}
void Car::check_y_pos() {
    if (remainingJumpSteps >= 0) {
        //to change velocity by 10 in one time step
        float force = m_car->GetMass() * 50 / (1 / 60.0); //f = mv/t
        //spread this over 6 time steps
        force /= 6.0;
        m_car->ApplyForce(b2Vec2(0, force), m_car->GetWorldCenter(), true);
        remainingJumpSteps--;
    }
}

Car::~Car() = default;

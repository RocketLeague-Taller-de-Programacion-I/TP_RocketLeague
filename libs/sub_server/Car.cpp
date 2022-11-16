//
// Created by franco on 07/11/22.
//

#include "Car.h"
#include "box2d/box2d.h"
#define NO_VEL 0
#define DEGTORAD 0.0174533
#define cojstaxisY 0.35

Car::Car(b2World* world) : turboOn(false), facingRight(true){
    b2Vec2 vertices[8];
    vertices[0].Set(-1.5f, -0.5f);
    vertices[1].Set(1.5f, -0.5f);
    vertices[2].Set(1.5f, 0.0f);
    vertices[3].Set(0.0f, 0.9f);
    vertices[4].Set(-1.15f, 0.9f);
    vertices[5].Set(-1.5f, 0.2f);

    chassis.Set(vertices, 6);
    bd.type = b2_dynamicBody;
    bd.position.Set(0.0f, 1.0f);
    m_car = world->CreateBody(&bd);
    fixture = m_car->CreateFixture(&chassis, 1.0f);
    fixture->SetRestitution(0.3);
}
void Car::goRight() {
    if (this->m_car->GetPosition().y > 4) {
        m_car->ApplyTorque(-500.0, true);
        return;
    }
    if (turboOn) {
        m_car->ApplyForce(b2Vec2(800, 0), m_car->GetWorldCenter(), true);
        turboOn = false;
        return;
    }
    m_car->ApplyForce(b2Vec2(500, 0), m_car->GetWorldCenter(), true);

}
void Car::goLeft() {
    if (this->m_car->GetPosition().y > 4) {
        m_car->ApplyTorque(500.0, true);
        return;
    }
    if (turboOn) {
        m_car->ApplyForce(b2Vec2(-800,0), m_car->GetWorldCenter(), true);
        turboOn = false;
        return;
    }
    m_car->ApplyForce(b2Vec2(-500, 0), m_car->GetWorldCenter(), true);
}
void Car::stop() {
    fixture->SetFriction(100);
}

void Car::turbo() {
    this->turboOn = true;
}
void Car::jump() {

    // 1/10th of a second at 60H
    check_y_pos();
    std::cout<<"Y: "<<this->m_car->GetPosition().y<<std::endl;
}

Car::~Car() = default;

void Car::check_y_pos() {
    if (Y() > 6) { return; }
    if (Y() > 3) {
        m_car->ApplyForce(b2Vec2(0, 1150), m_car->GetWorldCenter(), true);
        return;
    }
    m_car->ApplyForce(b2Vec2(0, 1500), m_car->GetWorldCenter(), true);
}
float Car::Y() {
    return this->m_car->GetPosition().y;
}
float Car::X() {
    return this->m_car->GetPosition().x;
}
/*
void Car::faceLeft() {
    b2Vec2 vertices[8];
    vertices[0].Set(1.5f,-0.5f);
    vertices[1].Set(-1.5f, -0.5f);
    vertices[2].Set(-1.5f, 0.0f);
    vertices[3].Set(0.0f, 0.9f);
    vertices[4].Set(1.15f, 0.9f);
    vertices[5].Set(1.5f, 0.2f);
    this->chassis.Set(vertices, 6);
    bd.type = b2_dynamicBody;
    bd.position.Set(this->m_car->GetPosition().x, this->m_car->GetPosition().y);
    fixture = m_car->CreateFixture(&chassis, 1.0f);
}
 */
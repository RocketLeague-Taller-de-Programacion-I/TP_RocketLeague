//
// Created by franco on 17/11/22.
//

#include <iostream>
#include <vector>
#include "MyContactListener.h"
#include "sub_server/server_box2d/Car.h"
#define BALL 0x0002
#define CAR 0x0003
#define GROUND 0x0004

MyContactListener::MyContactListener(std::vector<int> &contacts) : contacts(contacts) {
}
MyContactListener::~MyContactListener()  = default;
void MyContactListener::BeginContact(b2Contact* contact) {
    auto fA = contact->GetFixtureA();
    auto fB = contact->GetFixtureB();
    auto dataB = fB->GetUserData();
    auto dataA = fA->GetUserData();
    auto typeA = reinterpret_cast<MyFixtureUserDataType*> (dataA.pointer)->mObjectType;
    auto typeB = reinterpret_cast<MyFixtureUserDataType*> (dataB.pointer)->mObjectType;
    //  Registro mis contactos
    if (typeA != 2 and typeA != 4 and typeA != 0 and typeB == 2) { //  A es un auto y B es pelota
        auto id = reinterpret_cast<MyFixtureUserDataType*> (dataA.pointer)->id;
        this->contacts.push_back(id);
    }
    else if (typeB != 2 and typeB != 4 and typeB != 0 and typeA == 2)  { // B es un auto y A es pelota
        auto id = reinterpret_cast<MyFixtureUserDataType*> (dataB.pointer)->id;
        this->contacts.push_back(id);
    }
    //  Purple shot
    if ((typeA == 2 & typeB == 4)) {
        float magnitude=50;
        b2Vec2 force = b2Vec2((cos(fB->GetBody()->GetAngle()-4.7) * magnitude) ,(sin(fB->GetBody()->GetAngle()-4.7) * magnitude));
        auto forceCar = b2Vec2(force.x/3, force.y/3);
        fA->GetBody()->ApplyLinearImpulse(force, fA->GetBody()->GetPosition(), true);
        //  Impulso contrario al auto
        fB->GetBody()->ApplyLinearImpulse(-forceCar, fB->GetBody()->GetPosition(), true);
        return;
    }
    if ((typeB == 2 & typeA == 4)) {
        float magnitude=50;
        b2Vec2 force = b2Vec2((cos(fA->GetBody()->GetAngle()-4.7) * magnitude) ,(sin(fA->GetBody()->GetAngle()-4.7) * magnitude));
        auto forceCar = b2Vec2(force.x/3, force.y/3);
        fB->GetBody()->ApplyLinearImpulseToCenter(force, true);
        //  Impulso contrario al auto
        fA->GetBody()->ApplyLinearImpulse(-forceCar, fA->GetBody()->GetPosition(), true);
        return;
    }
    //  Gold shot

    /*  En estos dos casos los autos estan mirando para la izquierda, entonces su parte trasera será la derecha,
    * y como no hay precisión de cual es cada cuerpo (A auto o B bola ó viceversa) contemplo ambos casos.
     */
    if (typeA == 2 and typeB == 6) {
        bool right = reinterpret_cast<MyFixtureUserDataType*> (dataB.pointer)->facingRight;
        if (!right) {
            fA->GetBody()->ApplyForceToCenter(b2Vec2(5000.0, 0), true);
            return;
        }
    }
    if (typeB == 2 and typeA == 6) {
        bool right = reinterpret_cast<MyFixtureUserDataType *> (dataA.pointer)->facingRight;
        if (!right) {
            fB->GetBody()->ApplyForceToCenter(b2Vec2(5000.0, 0), true);
            return;
        }
    }
    if (typeB == 2 and typeA == 5) {
        bool right = reinterpret_cast<MyFixtureUserDataType *> (dataA.pointer)->facingRight;
        if (right) {
            fB->GetBody()->ApplyForceToCenter(b2Vec2(-5000.0, 0), true);
            return;
        }
    }
    if (typeA == 2 and typeB == 5) {
        bool right = reinterpret_cast<MyFixtureUserDataType *> (dataB.pointer)->facingRight;
        if (right) {
            fA->GetBody()->ApplyForceToCenter(b2Vec2(-5000.0, 0), true);
            return;
        }
    }
}


void MyContactListener::EndContact(b2Contact* contact) {}
void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {}
void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {}

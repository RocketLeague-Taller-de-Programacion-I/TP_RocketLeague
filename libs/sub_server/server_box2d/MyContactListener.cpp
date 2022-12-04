//
// Created by franco on 17/11/22.
//

#include <iostream>
#include "MyContactListener.h"
#include "sub_server/server_box2d/Car.h"

MyContactListener::MyContactListener() {
}
MyContactListener::~MyContactListener()  = default;
void MyContactListener::BeginContact(b2Contact* contact) {
    auto fA = contact->GetFixtureA();
    auto fB = contact->GetFixtureB();
    auto dataB = fB->GetUserData();
    auto dataA = fA->GetUserData();
    auto typeA = reinterpret_cast<MyFixtureUserDataType*> (dataA.pointer)->mObjectType;
    auto typeB = reinterpret_cast<MyFixtureUserDataType*> (dataB.pointer)->mObjectType;
    //  Purple shot
    if ((typeA == 2 & typeB == 4)) {
        float magnitude=50;
        b2Vec2 force = b2Vec2((cos(fB->GetBody()->GetAngle()-4.7) * magnitude) ,(sin(fB->GetBody()->GetAngle()-4.7) * magnitude));
        fA->GetBody()->ApplyLinearImpulse(force, fA->GetBody()->GetPosition(), true);
    }
    if ((typeB == 2 & typeA == 4)) {
        float magnitude=50;
        b2Vec2 force = b2Vec2((cos(fA->GetBody()->GetAngle()-4.7) * magnitude) ,(sin(fA->GetBody()->GetAngle()-4.7) * magnitude));
        fB->GetBody()->ApplyLinearImpulseToCenter(force, true);
    }
}


void MyContactListener::EndContact(b2Contact* contact) {}
void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {}
void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {}

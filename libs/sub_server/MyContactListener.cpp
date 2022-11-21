//
// Created by franco on 17/11/22.
//

#include <iostream>
#include "MyContactListener.h"
#include "Car.h"

MyContactListener::MyContactListener() {
}
MyContactListener::~MyContactListener()  = default;
void MyContactListener::BeginContact(b2Contact* contact) {
   std::cout<<"Begin contact"<<std::endl;
}

void MyContactListener::EndContact(b2Contact* contact) {
    std::cout<<"End contact"<<std::endl;
}
void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
    //  std::cout<<"PreSolve"<<std::endl;
}

void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
    b2Fixture* fixB = contact->GetFixtureB();
    auto dataB = fixB->GetUserData();
    std::cout<<reinterpret_cast<MyFixtureUserDataType*> (dataB.pointer)->mObjectType<<std::endl;
}

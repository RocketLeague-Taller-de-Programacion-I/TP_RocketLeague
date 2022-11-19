//
// Created by franco on 17/11/22.
//

#include "MyContactListener.h"
MyContactListener::MyContactListener() { }
MyContactListener::~MyContactListener()  = default;

void BeginContact(b2Contact* contact) {
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    auto bodyA = fixtureA->GetBody();
    auto dataA = bodyA->GetUserData();
    // if (dataA.pointer-> == )

}

void EndContact(b2Contact* contact) {

}

void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);
    //  Por si no es un contacto
    if (worldManifold.normal.y < -0.5f)
    {
        contact->SetEnabled(false);
    }
}

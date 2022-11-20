//
// Created by franco on 17/11/22.
//

#ifndef ROCKETLEAGUE_MYCONTACTLISTENER_H
#define ROCKETLEAGUE_MYCONTACTLISTENER_H


#include "box2d/box2d.h"

class MyContactListener : public b2ContactListener {
public:
    MyContactListener();
    ~MyContactListener();
    void BeginContact(b2Contact* contact);

    void EndContact(b2Contact* contact);
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};
#endif //ROCKETLEAGUE_MYCONTACTLISTENER_H

//
// Created by franco on 17/11/22.
//

#ifndef ROCKETLEAGUE_MYCONTACTLISTENER_H
#define ROCKETLEAGUE_MYCONTACTLISTENER_H


#include "box2d/box2d.h"

class MyContactListener : public b2ContactListener {
private:
    std::vector<int> &contacts;
public:
    MyContactListener(std::vector<int> &contacts);
    ~MyContactListener() override;
    void BeginContact(b2Contact* contact) override;

    void EndContact(b2Contact* contact) override;
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
};
#endif //ROCKETLEAGUE_MYCONTACTLISTENER_H
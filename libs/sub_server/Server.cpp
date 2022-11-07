//
// Created by franco on 24/10/22.
//

#include <iostream>
#include "Server.h"
#include "box2d/b2_world.h"

Server::Server() {
    b2Vec2 grav(0.0,0.2);
    b2World m_world(grav);
}
Server::~Server() { }
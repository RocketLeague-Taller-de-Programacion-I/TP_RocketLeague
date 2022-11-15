//
// Created by franco on 24/10/22.
//

#include <iostream>
#include "sub_server/Server.h"
//  Cada vez que queramos hacer include de box2d
#include "box2d/box2d.h"
#include "sub_server/Car.h"

int main(int argc, char const *argv[])
{
    b2Vec2 gravity(0, 0);
    b2World world(gravity);
    Car car(&world);
}

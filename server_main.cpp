//
// Created by franco on 24/10/22.
//

#include <iostream>
#include "sub_server/Server.h"
//  Cada vez que queramos hacer include de box2d
#include "box2d/box2d.h"

int main(int argc, char const *argv[]) {
    Server server(argv[1]);

    server.start();

}

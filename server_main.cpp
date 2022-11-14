//
// Created by franco on 24/10/22.
//

#include <iostream>
#include "sub_server/Server.h"
//  Cada vez que queramos hacer include de box2d
#include "box2d/box2d.h"

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        printf("Bad program call. Expected %s with one arguments.\n", argv[0]);
        return 1;
    }
    try {
        Server server(argv[1]);
        server.start();
        server.join();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch(...) {
        std::cerr << "Unknown exception\n";
        return 1;
    }
    return 0;
}

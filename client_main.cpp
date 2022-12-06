#include <iostream>
#include "sub_client/GameRenderer.h"

int main(int argc, char* argv[]) {
    try {
        GameRenderer gameRen(argv[1], argv[2]);
        gameRen.run();
    } catch (std::exception & e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

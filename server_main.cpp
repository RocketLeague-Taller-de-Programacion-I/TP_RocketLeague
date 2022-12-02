
#include "sub_server/Server.h"

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        printf("Bad program call. Expected %s with one arguments.\n", argv[0]);
        return 1;
    }
    try {
        Server server(argv[1]);
        server.start();

        std::string input;
        while (std::getline(std::cin, input)) {
            if (input == "q") {
                server.stop();
                server.join();
                break;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch(...) {
        std::cerr << "Unknown exception\n";
        return 1;
    }
    return 0;
}

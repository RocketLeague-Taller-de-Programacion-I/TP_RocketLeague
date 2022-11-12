//
// Created by franco on 24/10/22.
//

#include <iostream>
#include "Client.h"
#include "sub_common/BlockingQueue.h"


using namespace SDL2pp;
#define TESTDATA_DIR "../libSDL2pp/testdata"
static const float pi = 3.14159265358979323846f;
Client::Client(const char *host, const char *port) : skt_client(host, port) {}

Client::~Client() { }

void Client::start() {
    // create actions queue
    BlockingQueue<std::string> actionsQueue;
    // create updates queue
    BlockingQueue<std::string> updatesQueue;
    //launch ClientSender thread
    //launch ClientReceiver thread
    //launch render thread
    RenderThread render_thread(updatesQueue);
    render_thread.start();
    render_thread.join();
    updatesQueue.push("hola");
    std::string output;
    updatesQueue.tryPop(output);
    std::cout << output << std::endl;
    updatesQueue.tryPop(output);
    std::cout << output << std::endl;
}

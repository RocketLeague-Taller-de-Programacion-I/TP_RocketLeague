//
// Created by franco on 24/10/22.
//

#include <iostream>
#include "Client.h"


using namespace SDL2pp;
#define TESTDATA_DIR "../libSDL2pp/testdata"
static const float pi = 3.14159265358979323846f;
Client::Client(const char *host, const char *port) : skt_client(host, port) {}

Client::~Client() { }

void Client::start() {
    // create actions queue
    BlockingQueue<Action> actionsQueue;
    // create updates queue
    BlockingQueue<Action> updatesQueue;
    //launch ClientSender thread
    //launch ClientReceiver thread
    //launch render thread
    RenderThread render_thread(updatesQueue, actionsQueue);
    render_thread.start();
    render_thread.join();
    std::vector<Action> outputs;

    while(!actionsQueue.isEmpty()) {
        outputs.push_back(actionsQueue.pop());
        std::cout << "action of type: " << outputs.back().getType() << std::endl;
        outputs.pop_back();
    }
}

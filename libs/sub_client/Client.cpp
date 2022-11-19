//
// Created by franco on 24/10/22.
//

#include <iostream>
#include <regex>
#include "Client.h"

using namespace SDL2pp;
#define TESTDATA_DIR "../libSDL2pp/testdata"
static const float pi = 3.14159265358979323846f;
Client::Client(const char *host, const char *port) : skt_client(host, port) {}

Client::~Client() { }

void Client::start() {
    // create actions queue
    BlockingQueue<Action*> actionsQueue;
    // create updates queue
    BlockingQueue<Action*> updatesQueue;
    //launch ClientSender thread
     ClientSender sender(skt_client, actionsQueue);
    //launch ClientReceiver thread
//     ClientReceiver receiver(skt_client, updatesQueue);
//     receiver.start();
    //launch render thread

    RenderThread render_thread(updatesQueue, actionsQueue);
    sender.start();
    render_thread.start();

    render_thread.join();
    sender.join();
//    receiver.join();
}

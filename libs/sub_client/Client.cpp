//
// Created by franco on 24/10/22.
//

#include <iostream>
#include <regex>
#include "Client.h"

using namespace SDL2pp;
#define TESTDATA_DIR "../libSDL2pp/testdata"
static const float pi = 3.14159265358979323846f;
Client::Client(const char *host, const char *port) : skt_client(host, port), closed(false) {}

Client::~Client() { }

void Client::startThreads() {
    for (auto & t : threads){
        t->start();
    }
}

void Client::run() {
    try {

        BlockingQueue<std::shared_ptr<ClientAction>> actionsQueue;
        ProtectedQueue<std::shared_ptr<ClientUpdate>> updatesQueue;

        auto sender = new ThreadActionsSender(skt_client, actionsQueue);
        this->threads.push_back(sender);
        //launch ClientReceiver thread
//        auto receiver = new ClientReceiver(skt_client, updatesQueue);
        auto receiver = new UpdatesReceiverThread(skt_client, updatesQueue);
        this->threads.push_back(receiver);
        //
        //launch render thread
        auto render_thread = new RenderThread(updatesQueue, actionsQueue);
        this->threads.push_back(render_thread);

        startThreads();
        this->garbageCollector();

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en la función run" << std::endl;
    }
    this->cleanThreads();
}

void Client::cleanThreads() {
    for (auto & t : threads){
        t->join();
        delete t;
    }
}

void Client::stop() {
    closed = true;
    this->skt_client.shutdown(SHUT_RDWR);
    this->skt_client.close();
    this->join();
}


bool waitIfFinished(Thread* thread) {
    if (not thread->isRunning()) {
        thread->stop();
        thread->join();
        delete thread;
        return true;
    } else {
        return false;
    }
}

void Client::garbageCollector() {
    if (threads.empty()) return;
    this->threads.erase(std::remove_if(this->threads.begin(),
                                       this->threads.end(),
                                       waitIfFinished),
                        this->threads.end());
}
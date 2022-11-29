//
// Created by roby on 22/11/22.
//

#include "ThreadActionsSender.h"

ThreadActionsSender::ThreadActionsSender(Socket &skt_client, BlockingQueue<std::shared_ptr<ClientAction>> &actionsQueue) : skt_client(skt_client), actionsQueue(actionsQueue) {
    this->closed = false;
}

void ThreadActionsSender::run() {
    try {
        while (not closed) {
            auto action = actionsQueue.pop();
            std::vector<uint8_t> v = action->beSerialized();
            //  se iteran los comandos parseados y se envian al servidor
            for (uint8_t c : v) {
                skt_client.sendall(&c, sizeof(c), &closed);
            }
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en la función sender" << std::endl;
    }
}

void ThreadActionsSender::stop() {
}

ThreadActionsSender::~ThreadActionsSender() {
    delete &actionsQueue;
}
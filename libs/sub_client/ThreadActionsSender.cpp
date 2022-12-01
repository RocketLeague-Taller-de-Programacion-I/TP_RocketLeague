//
// Created by roby on 22/11/22.
//

#include "ThreadActionsSender.h"

ThreadActionsSender::ThreadActionsSender(Socket &skt_client, BlockingQueue<std::shared_ptr<ClientAction>> &actionsQueue) : skt_client(skt_client), actionsQueue(actionsQueue) {
    this->closed = false;
}

void ThreadActionsSender::run() {
    const std::function<void(void*, unsigned int)> callable = std::bind(&ThreadActionsSender::sendBytes, this, std::placeholders::_1, std::placeholders::_2);
    ClientProtocol p(callable);
    try {
        while (not closed) {
            auto action = actionsQueue.pop();
            uint8_t type = action->getType();
            sendBytes(&type, sizeof(action->getType()));

            p.serializeAction(action);
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

void ThreadActionsSender::sendBytes(void *bytes_to_send, int i) {
    if(!closed) {
        this->skt_client.sendall(bytes_to_send, i, &closed);
    }

}

//
// Created by roby on 22/11/22.
//

#include "ActionsSenderThread.h"

ActionsSenderThread::ActionsSenderThread(Socket &skt_client, BlockingQueue<std::optional<std::shared_ptr<ClientAction>>> &actionsQueue) : skt_client(skt_client), actionsQueue(actionsQueue) {
    this->closed = false;
}

void ActionsSenderThread::run() {
    const std::function<void(void*, unsigned int)> callable = std::bind(&ActionsSenderThread::sendBytes, this, std::placeholders::_1, std::placeholders::_2);
    ClientProtocol p(callable);
    try {
        while (not closed) {
            auto action = actionsQueue.pop();

            if(!action.has_value()) {
                break;
            }

            uint8_t type = action.value()->getType();
            sendBytes(&type, sizeof(action.value()->getType()));

            p.serializeAction(action.value());
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en la función sender" << std::endl;
    }
}

void ActionsSenderThread::stop() {
    closed = true;
    // create option null poitner tu push
    std::optional<std::shared_ptr<ClientAction>> null_pointer;
    actionsQueue.push(null_pointer);
}

void ActionsSenderThread::sendBytes(void *bytes_to_send, int i) {
    if(!closed) {
        this->skt_client.sendall(bytes_to_send, i, &closed);
    }
}

ActionsSenderThread::~ActionsSenderThread() {}

//
// Created by roby on 22/11/22.
//

#include "ThreadActionsSender.h"

ThreadActionsSender::ThreadActionsSender(Socket &skt_client, BlockingQueue<ClientAction*> &queue) : skt_client(skt_client), actionsQueue(queue) {
    this->closed = false;
}

void ThreadActionsSender::run() {
    try {
        while (not closed) {
            auto action = actionsQueue.pop();
//            std::vector<uint8_t> v = p.serializeAction(action);
            std::vector<uint8_t> v = action->beSerialized();
            //  se iteran los comandos parseados y se envian al servidor
            for (uint8_t c : v) {
                skt_client.sendall(&c, sizeof(c), &closed);
            }
            //  send the NOP instruccion
            uint8_t nop = 0;
            skt_client.sendall(&nop, sizeof(nop), &closed);
            // delete the action
            delete action;
        }
        running = false;
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
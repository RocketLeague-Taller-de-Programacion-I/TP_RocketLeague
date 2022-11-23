//
// Created by lucaswaisten on 12/11/22.
//

#include "ClientSender.h"

ClientSender::ClientSender(Socket &skt_client, BlockingQueue<Action *> *queue, uint8_t idClient)
        : skt_client(skt_client), idClient(idClient), actionsQueue(queue) {
    this->closed = false;
}

void ClientSender::run() {
    Protocolo p;
    try {
        while (not closed) {
            auto action = actionsQueue->pop();
            std::vector<uint8_t> v = p.serializeAction(action);
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

void ClientSender::stop() {
}

ClientSender::~ClientSender() {
    delete actionsQueue;
}

BlockingQueue<Action *>* ClientSender::getQueue() const {
    return this->actionsQueue;
}

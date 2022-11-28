//
// Created by lucaswaisten on 12/11/22.
//

#include "ClientSender.h"

ClientSender::ClientSender(Socket &skt_client, BlockingQueue<ServerUpdate *> *queue, uint8_t idClient)
        : skt_client(skt_client), idClient(idClient), actionsQueue(queue) {
    this->closed = false;
}

void ClientSender::run() {
    Protocolo p;
    try {
        while (not closed) {
            auto action = actionsQueue->pop();
//            std::vector<uint8_t> v = p.serializeAction(action);
            std::vector<uint16_t> v = action->beSerialized();
            //  se iteran los comandos parseados y se envian al servidor
            for (uint16_t c : v) {
                skt_client.sendall(&c, sizeof(c), &closed);
            }
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

BlockingQueue<ServerUpdate *> * ClientSender::getQueue() const {
    return this->actionsQueue;
}

//
// Created by lucaswaisten on 12/11/22.
//

#include "ClientSender.h"

ClientSender::ClientSender(Socket &skt_client, BlockingQueue<std::shared_ptr<ServerUpdate>> *queue, uint8_t idClient)
        : skt_client(skt_client), idClient(idClient), actionsQueue(queue) {
    this->closed = false;
}

void ClientSender::run() {
    const std::function<void(void*, unsigned int)> callable = std::bind(&ClientSender::sendBytes, this, std::placeholders::_1, std::placeholders::_2);
    Protocolo p(callable);
    try {
        while (not closed) {
            auto action = actionsQueue->pop();
            uint8_t type = action->getType();
            sendBytes(&type, sizeof(action->getType()));

            p.serializeUpdate(action);
            // delete the action
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en la función sender" << std::endl;
    }
}

void ClientSender::sendBytes(void* bytes_to_send, unsigned int size) {
    if(!closed) {
        this->skt_client.sendall(bytes_to_send, size, &closed);
    }
}
void ClientSender::stop() {
}

ClientSender::~ClientSender() {
    delete actionsQueue;
}

BlockingQueue<std::shared_ptr<ServerUpdate>> * ClientSender::getQueue() const {
    return this->actionsQueue;
}

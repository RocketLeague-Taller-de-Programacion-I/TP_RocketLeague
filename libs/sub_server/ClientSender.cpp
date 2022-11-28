//
// Created by lucaswaisten on 12/11/22.
//

#include "ClientSender.h"

ClientSender::ClientSender(Socket &skt_client, BlockingQueue<ServerUpdate *> *queue, uint8_t idClient)
        : skt_client(skt_client), idClient(idClient), actionsQueue(queue) {
    this->closed = false;
}

void ClientSender::run() {
    try {
        while (not closed) {
            auto action = actionsQueue->pop();
//            std::vector<uint8_t> v = p.serializeAction(action);
            std::vector<uint8_t> v = action->beSerialized();
            //  se iteran los comandos parseados y se envian al servidor
            for (uint8_t c : v) {
                skt_client.sendall(&c, sizeof(c), &closed);
            }
            // delete the action
//            delete action; //TODO: Donde deletear?
        }
        running = false;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en la función sender" << std::endl;
    }
}

void ClientSender::sendBytes(uint8_t& size) {
    if(!closed) {
        std::string answer_string = create_answer_string(movements);

        uint16_t size_string = htons(answer_string.size());
        this->skt.sendall(answer_string.c_str(), ntohs(size_string), &was_closed);

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

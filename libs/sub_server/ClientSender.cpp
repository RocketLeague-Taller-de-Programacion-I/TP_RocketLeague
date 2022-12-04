//
// Created by lucaswaisten on 12/11/22.
//

#include "ClientSender.h"

ClientSender::ClientSender(Socket &skt_client, BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>> *queue, uint8_t idClient)
        : skt_client(skt_client), idClient(idClient), updatesQueue(queue) {
    this->closed = false;
}

void ClientSender::run() {
    ServerProtocolo protocolo;
    try {
        while (not closed) {
            auto update = updatesQueue->pop();

            // check if we push a nullpointer to close the thread
            if(!update.has_value()) {
                break;
            }

            uint8_t type = update.value()->getType();
            sendBytes(&type, sizeof(update.value()->getType()));

            std::function<void(void*, unsigned int)> sendCallable =
                    std::bind(&ClientSender::sendBytes, this, std::placeholders::_1, std::placeholders::_2);

            protocolo.serializeUpdate(update.value(), sendCallable);
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
    closed = true;
    // create option null poitner tu push
    std::optional<std::shared_ptr<ServerUpdate>> null_pointer;
    updatesQueue->push(null_pointer);
}

ClientSender::~ClientSender() {
    delete updatesQueue;
}

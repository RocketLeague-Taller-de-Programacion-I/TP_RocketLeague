//
// Created by lucaswaisten on 12/11/22.
//

#include "ClientReceiver.h"


ClientReceiver::ClientReceiver(Socket &skt_client, ProtectedQueue<ServerAction *> *updatesQueue, uint8_t idClient)
        : skt_client(skt_client), idClient(idClient), updatesQueue((updatesQueue)) {
    this->closed = false;
}

void ClientReceiver::run() {
    Protocolo p;
    try {
        while (!closed) {
            std::vector<uint8_t> data;
            data.push_back(idClient);
            uint8_t byte_to_read;

            this->skt_client.recvall(&byte_to_read, sizeof(byte_to_read), &closed);

            while (byte_to_read != NOP && !closed) {
                data.push_back(byte_to_read);
                this->skt_client.recvall(&byte_to_read, sizeof(byte_to_read), &closed);
            }
            // TODO: Cambiar protocolo
            // form the Action from the data
            auto action = p.deserializeData(data);
            // push the action to the queue
            updatesQueue->push(action);
        }
        running = false;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en la función receiver" << std::endl;
    }
}
void ClientReceiver::stop() {}

void ClientReceiver::setQueue(ProtectedQueue<ServerAction *> *pQueue) {
    clearQueue();
    this->updatesQueue = pQueue;
}
void ClientReceiver::clearQueue() {
    std::vector<ServerAction*> elements = this->updatesQueue->popAll();
    for (auto &element : elements) {
        delete element;
    }
    elements.clear();
}

ClientReceiver::~ClientReceiver() {
    delete this->updatesQueue;
    closed = false;
    this->join();
}

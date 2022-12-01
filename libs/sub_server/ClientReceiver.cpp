//
// Created by lucaswaisten on 12/11/22.
//

#include "ClientReceiver.h"


ClientReceiver::ClientReceiver(Socket &skt_client, ProtectedQueue<std::shared_ptr<ServerAction>> *updatesQueue, uint8_t idClient)
        : skt_client(skt_client), idClient(idClient), updatesQueue((updatesQueue)) {
    this->closed = false;
}

void ClientReceiver::run() {
    try {
        while (!closed) {
            uint8_t actionType;

            this->skt_client.recvall(&actionType, sizeof(actionType), &closed);

            std::function<void(void *bytes_to_read, int size)> bytes_receiver_callable =
                    std::bind(&ClientReceiver::receiveBytes, this, std::placeholders::_1 ,std::placeholders::_2);

            // form the Action from the data
            auto action = Protocolo::deserializeData(idClient, actionType, bytes_receiver_callable);
            // push the action to the queue
            updatesQueue->push(action);
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en la función receiver" << std::endl;
    }
}
void ClientReceiver::stop() {}

void ClientReceiver::setQueue(ProtectedQueue<std::shared_ptr<ServerAction>> *pQueue) {
    clearQueue();
    this->updatesQueue = pQueue;
}
void ClientReceiver::receiveBytes(void *bytes_to_read, int size) {
    if(!closed) {
        this->skt_client.recvall(bytes_to_read, size, &closed);
    }
}

void ClientReceiver::clearQueue() {
    std::queue<std::shared_ptr<ServerAction>> elements = this->updatesQueue->popAll();
}

ClientReceiver::~ClientReceiver() {
    delete this->updatesQueue;
    closed = false;
    this->join();
}

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
            uint8_t byte_to_read;

            this->skt_client.recvall(&byte_to_read, sizeof(byte_to_read), &closed);

            std::function<void(std::vector<uint8_t>&, uint8_t&)> bytes_receiver_callable =
                    std::bind(&ClientReceiver::receiveBytes, this, std::placeholders::_1 ,std::placeholders::_2);

            // form the Action from the data
            auto action = ServerProtocolo::deserializeData(idClient, byte_to_read, bytes_receiver_callable);
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
void ClientReceiver::receiveBytes(std::vector<uint8_t>& bytes_to_read, uint8_t& size) {
    if(!closed) {
        this->skt_client.recvall(bytes_to_read.data(), size, &closed);
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

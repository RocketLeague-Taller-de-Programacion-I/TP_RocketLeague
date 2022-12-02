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

            auto action = ServerProtocolo::deserializeData(idClient, actionType, bytes_receiver_callable);

            updatesQueue->push(action);
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en la función receiver" << std::endl;
    }
}

void ClientReceiver::receiveBytes(void *bytes_to_read, int size) {
    if(!closed) {
        this->skt_client.recvall(bytes_to_read, size, &closed);
    }
}

void ClientReceiver::stop() {
    closed = true;
}

ClientReceiver::~ClientReceiver() {}

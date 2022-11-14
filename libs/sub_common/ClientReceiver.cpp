//
// Created by lucaswaisten on 12/11/22.
//

#include "ClientReceiver.h"

ClientReceiver::ClientReceiver(Socket &skt_client,BlockingQueue <Action> &actionsQueue)
    : skt_client(skt_client),
    actionsQueue(actionsQueue) {
    this->closed = false;
}

void ClientReceiver::run() {
    Protocolo p;
    while (!closed) {
        std::vector<uint8_t> data;
        uint8_t byte_to_read;

        this->skt_client.recvall(&byte_to_read, sizeof(byte_to_read), &closed);

        while (byte_to_read != NOP && !closed) {
            data.push_back(byte_to_read);
            this->skt_client.recvall(&byte_to_read, sizeof(byte_to_read), &closed);
        }

        //crear action con protocolo
    }

}

void ClientReceiver::stop() {}

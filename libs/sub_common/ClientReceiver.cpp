//
// Created by lucaswaisten on 12/11/22.
//

#include "ClientReceiver.h"

ClientReceiver::ClientReceiver(Socket &skt_client, BlockingQueue<Action> &updatesQueue)
    : skt_client(skt_client), updatesQueue(updatesQueue) {
    this->closed = false;
}

void ClientReceiver::run() {
    Protocolo p;
    try {
        while (!closed) {
            std::vector<uint8_t> data;
            uint8_t byte_to_read;

            this->skt_client.recvall(&byte_to_read, sizeof(byte_to_read), &closed);

            while (byte_to_read != NOP && !closed) {
                data.push_back(byte_to_read);
                this->skt_client.recvall(&byte_to_read, sizeof(byte_to_read), &closed);
            }
            // form the Action from the data
            Action action = p.deserializeToAction(data);
            // push the action to the queue
            updatesQueue.push(action);
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en la función receiver" << std::endl;
    }
}
void ClientReceiver::stop() {}

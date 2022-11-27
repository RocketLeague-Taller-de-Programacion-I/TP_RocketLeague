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

            // Recuerden refactorizar el protocolo
            // ya sea, metiendo un opcode de 4 bytes delimitador del mensaje, por ejemplo 0xcafebeb0 (ahi usarian recv_some),
            // o definiendo el tamaño de mensaje luego del opcode

            // Esto funciona. A modo de comentario, 
            // recuerden que por cada recvall se hace al menos una llamada a una syscall y por lo tanto un context switch. 
            // Lo ideal, con su protocolo por como esta ahora, es recibir con recv_some y guardar el remanente, tal como lo explico fefo en la presentación del tp2. 
            // El mismo coment aplica para el sender. Pero para este es mas facil solucionarlo: se crean el vector antes y luego lo envian con sendall. 
            while (byte_to_read != NOP && !closed) {
                data.push_back(byte_to_read);
                this->skt_client.recvall(&byte_to_read, sizeof(byte_to_read), &closed);
            }
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

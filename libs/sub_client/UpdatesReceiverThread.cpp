//
// Created by roby on 22/11/22.
//

#include "UpdatesReceiverThread.h"

#define NOP 0x00

UpdatesReceiverThread::UpdatesReceiverThread(Socket &skt_client, ProtectedQueue<ClientUpdate*> &updatesQueue)
        : skt_client(skt_client), updatesQueue(updatesQueue) {
    this->closed = false;
}

void UpdatesReceiverThread::run() {
    try {
        while (!closed) {
            std::vector<uint8_t> data;
            uint8_t byte_to_read;

            this->skt_client.recvall(&byte_to_read, sizeof(byte_to_read), &closed);

            while (byte_to_read != NOP && !closed) {
                data.push_back(byte_to_read);
                this->skt_client.recvall(&byte_to_read, sizeof(byte_to_read), &closed);
            }
            // form the Update from the data
            auto action = ClientProtocol::deserializeData(data);
            // push the action to the queue
            updatesQueue.push(action);
        }
        running = false;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en la función receiver" << std::endl;
    }
}
void UpdatesReceiverThread::stop() {}

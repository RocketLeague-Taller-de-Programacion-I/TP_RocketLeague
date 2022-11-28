//
// Created by roby on 22/11/22.
//

#include <netinet/in.h>
#include "UpdatesReceiverThread.h"

#define NOP 0x00

UpdatesReceiverThread::UpdatesReceiverThread(Socket &skt_client, ProtectedQueue<std::shared_ptr<ClientUpdate>> &updatesQueue)
        : skt_client(skt_client), updatesQueue(updatesQueue) {
    this->closed = false;
}

void UpdatesReceiverThread::run() {
    try {
        while (!closed) {
            uint8_t byte_to_read;
            //type byte
            this->skt_client.recvall(&byte_to_read, sizeof(byte_to_read), &closed);
            //callback function to receiveBytes
            std::function<void(void*, int)> bytes_receiver_callable =
                    std::bind(&UpdatesReceiverThread::receiveBytes, this, std::placeholders::_1 ,std::placeholders::_2);

            // form the Update from the data
            auto action = ClientProtocol::deserializeData(byte_to_read,bytes_receiver_callable);
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

void UpdatesReceiverThread::receiveBytes(void *bytes_to_read, int size) {
    if(!closed) {
        this->skt_client.recvall(bytes_to_read, size, &closed);
    }
}

void UpdatesReceiverThread::stop() {}

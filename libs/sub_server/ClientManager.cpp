//
// Created by lucaswaisten on 07/11/22.
//

#include <sys/socket.h>
#include "ClientManager.h"
#include "sub_common/Action.h"
#include "sub_common/Update.h"
#include "sub_common/ClientReceiver.h"
#include "sub_common/ClientSender.h"

ClientManager::ClientManager(Socket &aClient,
                             GameManager &aGameManager) :
                             client(aClient),
                             gameManager(aGameManager),
                             closed(false){}

void ClientManager::run() {
    BlockingQueue<Action> receiverQueue;
    BlockingQueue<Action> senderQueue;

    std::vector<uint8_t> data(1);
    data.push_back(1);
    Action action(CREATE_ROOM, data);
    senderQueue.push(action);

    auto *threadReceiver = new ClientReceiver(client, receiverQueue);
    auto *threadSender = new ClientSender(client, senderQueue);

    threadReceiver->start();
    threadSender->start();

    while (not closed) {
        /*
         * logica de lectura de los comandos
         * recividos por el socket
         */
       // std::string mensaje(this->recivMesage());
       /*
        * gameManager tiene las partidas, por lo tanto
        * tendre que pasarle los nuevos comandos
        * y que me devuelva los parametros para enviar
        * nuevamente por medio del socket
        */
        }
}

bool ClientManager::joinThread() {
    if (not closed) return false;
    return this->endManager();
}

bool ClientManager::endManager() {
    closed = true;
    client.shutdown(SHUT_RDWR);
    client.close();
    this->join();
    return closed;
}

void ClientManager::stop() {

}

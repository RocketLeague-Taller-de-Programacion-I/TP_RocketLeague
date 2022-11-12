//
// Created by lucaswaisten on 07/11/22.
//

#include <sys/socket.h>
#include "ClientManager.h"

ClientManager::ClientManager(Socket &aClient,
                             GameManager &aGameManager) :
                             client(std::move(aClient)),
                             gameManager(aGameManager),
                             closed(false){}

void ClientManager::run() {
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

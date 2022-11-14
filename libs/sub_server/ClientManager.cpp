//
// Created by lucaswaisten on 07/11/22.
//

#include <sys/socket.h>
#include "ClientManager.h"
#include "sub_common/Action.h"
#include "ClientReceiver.h"
#include "ClientSender.h"

ClientManager::ClientManager(Socket &aClient,
                             GameManager &aGameManager) :
                             client(aClient),
                             gameManager(aGameManager),
                             closed(false){}

void ClientManager::run() {
    BlockingQueue<Action> receiverQueue;
    BlockingQueue<Update> senderQueue;

    auto *threadReceiver = new ClientReceiver(client, receiverQueue);
    auto *threadSender = new ClientSender(client, senderQueue);

    threadReceiver->start();
    threadSender->start();

    do {
        auto action = receiverQueue.pop();
        action.excecute(gameManager, this);
        /*
         * posiblemente el push tenga que ser por movimiento
         * ya que se va a eliminar una vez salido de este scope
         * el update
         */
        //gameManager.sendUpdate(update);
    } while (not closed);
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

void ClientManager::attendClient(unsigned long aId) {
    this->id = aId;
    this->start();
}


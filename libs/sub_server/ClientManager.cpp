//
// Created by lucaswaisten on 07/11/22.
//
#pragma once
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

    std::vector<uint8_t> data;
    uint8_t byte_to_read;
    /*
     * type of first byte to read:
     *  - CREATE_ROOM
     *  - JOIN_ROOM
     */
    this->client.recvall(&byte_to_read, sizeof(byte_to_read), &closed);

    while (byte_to_read != NOP && !closed) {
        data.push_back(byte_to_read);
        this->skt_client.recvall(&byte_to_read, sizeof(byte_to_read), &closed);
    }
    // form the Action from the data
    ActionCrearPartida o Joinear action = p.deserializarCrearcionDePartida(data);


    BlockingQueue<Action> receiverQueue;
    BlockingQueue<Update> senderQueue;
    monitor.h
    monitor.ejecutar(ActionCrearPartida action);
    monitor.ejecutar(ACtionunirtsdbf);

    monitor.ejecutar(action):


    Partida(queuerecibir, queuesender)
    Partida.run()

    std::vector<uint8_t> data(1);
    data.push_back(1);
    Action action(CREATE_ROOM, data);
    senderQueue.push(action);

    auto *threadReceiver = new ClientReceiver(client, receiverQueue);
    auto *threadSender = new ClientSender(client, senderQueue);

    threadReceiver->start();
    threadSender->start();
    /*
     * reciv de create o join

    client.recvall();

    BlockingQueue<Action> receiverQueue;
    BlockingQueue<Update> senderQueue;

    auto *threadReceiver = new ClientReceiver(client, receiverQueue);
    auto *threadSender = new ClientSender(client, senderQueue);

    threadReceiver->start();
    threadSender->start();

    do {
        auto action = receiverQueue.pop();

         * le paso la cola sender, que es la data necesaria para la comunicacion

        action.excecute(gameManager, this);

         * posiblemente el push tenga que ser por movimiento
         * ya que se va a eliminar una vez salido de este scope
         * el update

        //gameManager.sendUpdate(update);
    } while (not closed);

         * logica de lectura de los comandos
         * recividos por el socket

       // std::string mensaje(this->recivMesage());

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

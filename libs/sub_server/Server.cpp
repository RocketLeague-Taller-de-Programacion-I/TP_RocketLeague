//
// Created by franco on 24/10/22.
//

#include <iostream>
#include <algorithm>
#include <sys/socket.h>
#include "Server.h"
#include "ClientReceiver.h"
#include "ClientSender.h"
#include "sub_common/MonitorSocket.h"

Server::Server(const std::string &servname)
        : closed(false),
          accept_skt(servname.c_str()) {}

Server::~Server() = default;
/*
 * Mientras closed sea false aceptara clientes.
 * A cada manager de cliente le pasará el gameManager y
 * lo guarda en un array de senders.
 *
 * Ira limpiando aquellos senders que han finalizado
 */
void Server::run() {
    // Server tiene una cola bloqueante de acciones de acciones
    /*
     * definir la cola bloqueante por aca, ya sea de atributo o lo que fuere
     */
    while(not closed){
        /*
         * El socket como son dos hilos los que acceden, tiene que tener un lock para resguardar
         * ver si se puede crear el socket dinamico
         */
        //Socket client = accept_skt.accept();
        MonitorSocket monitorSocket(accept_skt.accept());
        // auto *client = new DynamicSocket(accept_skt.accept());
        auto *threadReciver = new ClientReceiver(monitorSocket);
        auto *threadSender = new ClientSender(monitorSocket);
        this->senders.push_back(threadSender); // le tengoq ue pasar la cola reciver action
        this->recivers.push_back(threadReciver); // le tengo que pasar la cola update
        threadReciver->start();
        threadSender->start();
        /*
         * aca sever llama a un metodo para que ni bien llegue una action
         * la lea y se ejectuta de parte del servidor.
         * El servir subira el update a la cola de update. Y llamaria a todos los sender para que actualizen
         * las nuevas posiciones del respectivo cliente
         */

        /*
         *
         */
        //
        this->garbageCollector();
    }
   /* GameManager gameManager;

    try {
        while (not closed) {
           Socket client = accept_skt.accept();
           auto *manager = new ClientManager(client,gameManager);
           this->senders.push_back(manager);
           manager->start();
           this->garbageCollector();
        }
    } catch (...) {}
    gameManager.cleanGames();
    this->cleanManagers();*/
}
/*
 * Consulta a cada manager si finalizo.
 *      En caso de true lo elimina y cada del vector.
 *      En caso de false no lo elimina.
 */
void Server::garbageCollector() {
    senders.erase(std::remove_if(senders.begin(),
                                 senders.end(),
                                 [](ClientSender *manager)
                                     { if (manager->joinThread()) {
                                         delete manager;
                                         return true;
                                     }
                                         return false;
                                     }),
                  senders.end());
    recivers.erase(std::remove_if(recivers.begin(),
                                 recivers.end(),
                                 [](ClientReceiver *manager)
                                 { if (manager->joinThread()) {
                                     delete manager;
                                     return true;
                                 }
                                     return false;
                                 }),
                  recivers.end());
}
/*
 * Limpia a los senders al igual que
 * garbageCollector pero sin preguntar por
 * su estado.
 */
void Server::cleanManagers() {
    for (auto & manager : senders){
        manager->join();
        delete manager;
    }
    for (auto & manager : recivers){
        manager->join();
        delete manager;
    }
}
/*
 * Cierra el socket y el hilo.
 */
void Server::stop() {
    closed = true;
    this->accept_skt.shutdown(SHUT_RDWR);
    this->accept_skt.close();
    this->join();
}

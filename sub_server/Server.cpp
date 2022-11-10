//
// Created by franco on 24/10/22.
//

#include <iostream>
#include <algorithm>
#include <sys/socket.h>
#include "Server.h"

Server::Server(const std::string &servname)
        : cerrado(false),
        acept_skt(servname.c_str()) {}

Server::~Server() = default;
/*
 * Mientras closed sea false aceptara clientes.
 * A cada manager de cliente le pasará el gameManager y
 * lo guarda en un array de managers.
 *
 * Ira limpiando aquellos managers que han finalizado
 */
void Server::run() {
    GameManager gameManager;

    try {
        while (not cerrado) {
           Socket client = acept_skt.accept();
           auto *manager = new ClientManager(client,gameManager);
           this->managers.push_back(manager);
           manager->start();
           this->cleanManagersEnds();
        }
    } catch (...) {}
    gameManager.cleanGames();
    this->cleanManagers();
}
/*
 * Consulta a cada manager si finalizo.
 *      En caso de true lo elimina y cada del vector.
 *      En caso de false no lo elimina.
 */
void Server::cleanManagersEnds() {
    managers.erase(std::remove_if(managers.begin(),
                                     managers.end(),
                                     [](ClientManager *manager)
                                     { if (manager->joinThread()) {
                                         delete manager;
                                         return true;
                                     }
                                         return false;
                                     }),
                      managers.end());
}
/*
 * Limpia a los managers al igual que
 * cleanManagersEnds pero sin preguntar por
 * su estado.
 */
void Server::cleanManagers() {
    for (auto & manager : managers){
        manager->join();
        delete manager;
    }
}
/*
 * Cierra el socket y el hilo.
 */
void Server::stop() {
    cerrado = true;
    this->acept_skt.shutdown(SHUT_RDWR);
    this->acept_skt.close();
    this->join();
}

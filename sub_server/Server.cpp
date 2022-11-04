//
// Created by franco on 24/10/22.
//

#include <iostream>
#include "Server.h"

Server::Server(const std::string &servname)
        : cerrado(false),
        acept_skt(servname.c_str()) {}

Server::~Server() {}

void Server::run() {
    GameManager gameManager;

    try {
        while (not cerrado) {
           // Socket client = acept_skt.accept();
           // auto *manager = new ClientManager(cliente,monitorCliente);
           // manejadores.push_back(manager);
           // manager->atenderCliente();
           // this->limpiarManejadoresFinalizados();
        }
    } catch (...) {}
    //monitorCliente.limpiarPartidas();
    //this->limpiarManejadores(); try {
    //    while(not cerrado)
    //}
}

void Server::stop() {

}





#include "Server.h"

#define INITIAL_ID_PLAYER 3

Server::Server(const char *port)
        : closed(false),
          accept_skt(port) {}

void Server::run() {
    GameManager gameManager;
    uint8_t idPlayer = INITIAL_ID_PLAYER;
    try {
        while (not closed) {

            Socket client = accept_skt.accept();

            auto *manager = new ClientManager(idPlayer, client, gameManager);
            managers.push_back(manager);
            manager->start();

            idPlayer++;
        }
    } catch (...) {}
    cleanManagers();
    gameManager.cleanGames();
}

void Server::cleanManagers() {
    for (auto & manager : managers) {
        manager->stop();
        manager->join();
        delete manager;
    }
}

void Server::stop() {
    closed = true;
    accept_skt.shutdown(2);
    accept_skt.close();
}

Server::~Server() {}
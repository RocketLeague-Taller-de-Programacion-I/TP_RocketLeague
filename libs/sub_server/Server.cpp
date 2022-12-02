//
// Created by franco on 24/10/22.
//

#include "Server.h"
#include "box2d/b2_world.h"

#define INITIAL_ID_PLAYER 2

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

            garbageCollector();
        }
    } catch (...) {}
    gameManager.cleanGames();
    cleanManagers();
}

void Server::garbageCollector() {
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

void Server::cleanManagers() {
    for (auto & manager : managers){
        manager->stop();
        manager->join();
        delete manager;
    }
}

void Server::stop() {
    closed = true;
    cleanManagers();
    accept_skt.shutdown(2);
    accept_skt.close();
}

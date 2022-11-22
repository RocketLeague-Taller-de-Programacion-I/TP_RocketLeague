//
// Created by franco on 24/10/22.
//

#include "Server.h"

#include "box2d/b2_world.h"

Server::Server(const char *port)
        : closed(false),
          accept_skt(port) {
    b2Vec2 grav(0.0,0.2);
    b2World m_world(grav);
}

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
    GameManager gameManager;
    idPlayer_t idPlayer = 1;
    try {
        while (not closed) {
            /*
             * El socket como son dos hilos los que acceden, tiene que tener un lock para resguardar
             * ver si se puede crear el socket dinamico
             */
            Socket client = accept_skt.accept();

            auto *manager = new ClientManager(client,gameManager);
            this->managers.push_back(manager);
            /*
             * Attend client:
             *  - Set the ID manager
             *  - Start the thread
             */
            manager->attendClient(idPlayer);
            idPlayer++;

            this->garbageCollector();
        }
    } catch (...) {}
    //gameManager.cleanGames();
    this->cleanManagers();
}
/*
 * Consulta a cada manager si finalizo.
 *      En caso de true lo elimina y cada del vector.
 *      En caso de false no lo elimina.
 */
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
/*
 * Limpia a los senders al igual que
 * garbageCollector pero sin preguntar por
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
    closed = true;
    this->accept_skt.shutdown(SHUT_RDWR);
    this->accept_skt.close();
    this->join();
}

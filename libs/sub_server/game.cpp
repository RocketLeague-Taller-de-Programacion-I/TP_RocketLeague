//
// Created by lucaswaisten on 04/11/22.
//

#include "game.h"

// pasar name por referencia
Game::Game(int capacity,
           std::string  name,
           ProtectedQueue<ServerAction *> *pQueue) :
        match(name, capacity),
        capacity(capacity),
        playerOnLine(0),
        gameName(std::move(name)),
        queue(pQueue) {}

std::string Game::information() {
    return gameName+" "+std::to_string(playerOnLine)+"/"+std::to_string(capacity);
}
void Game::joinPlayer(uint8_t& id, BlockingQueue<ServerUpdate *> *sender) {
    playerOnLine++;
    mapSender.insert(std::pair<uint8_t ,BlockingQueue<ServerUpdate*>*>(id, sender));
    if (playerOnLine == capacity){
//        int local = this->match.local();
//        int visit = this->match.visit();
        start();
    }
}

void Game::run() {
    // pop actions from queue, processed them and broadcast them
    /* ServerUpdateWorld
     * * std::vector<uint8_t> matchInfo = this->match.matchInfo();
     * ServerUpdateWorld* update(id, matchInfo)
     *
     */
    while (true) {

    }

    /*
     * // el game loop hace mas o menos lo siguiente
     *  ```
     *  while (...) {
     *      // esto o hacen un for loop de 0 a N (N lo definen ustedes) y popean (si no hay nada, salen del for)
     *      auto actions = queue.popAll();
     *      // match se encarga de loopear sobre el arreglo de acciones y las ejecuta (estas modifican el estado del juego)
     *      match.update(&actions);
     *      // avanzamos el mundo en un dt
     *      match.step(TICK_RATE);
     *
     *      auto states = match.getGameState();
     *      auto update = std::make_unique<StateUpdate>(new StateUpdate(std::move(states)));
     *      // ojo, no todos los updates serán broadcasteados (por ejemplo, el nitro actual de un player le interesa solo a ese player)
     *      broadcastUpdate(std::move(update));
     *      // dormimos durante un tick
     *      usleep(TICK_RATE);
     *      // checkeamos si la partida llego a la totalidad de ticks!
     *      ...
     *  }
     *  ```
     */
}

bool Game::isFull() const {
    return playerOnLine == capacity;
}

ProtectedQueue<ServerAction *> * Game::getQueue() {
    return queue;
}

void Game::stop() {}

void Game::broadcastUpdate(ServerUpdate *update) {
    for (auto & sender : mapSender) {
        sender.second->push(update);
    }
}

void Game::brodcastUpdateGameEvents(std::vector<ServerUpdate *> updates) {
    for (auto & sender : mapSender) {
        for (auto & update : updates) {
            sender.second->push(update);
        }
    }
}

Game::~Game() {
    for (auto & sender : mapSender) {
        delete sender.second;
    }
    join();
}

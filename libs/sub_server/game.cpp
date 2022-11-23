//
// Created by lucaswaisten on 04/11/22.
//

#include "game.h"
#include "Action.h"
#include "ActionUpdate.h"

Game::Game(int capacity,
           std::string  name,
           ProtectedQueue<Action *> *pQueue) :
        match(name, capacity),
        capacity(capacity),
        playerOnLine(0),
        gameName(std::move(name)),
        queue(pQueue) {}

std::string Game::information() {
    return gameName+" "+std::to_string(playerOnLine)+"/"+std::to_string(capacity);
}
void Game::joinPlayer(uint8_t id, BlockingQueue<Action*> *sender) {
    playerOnLine++;
    mapSender.insert(std::pair<uint8_t ,BlockingQueue<Action*>*>(id, sender));
    if (playerOnLine == capacity){
//        int local = this->match.local();
//        int visit = this->match.visit();
        start();
        // broadcast new update to all clients
        std::string mensaje = "OK";
        Action* update = new ActionUpdate(id, mensaje); //creacion de partida, devuelve el id
        broadcastUpdate(update);
    }
}

void Game::run() {
    // pop actions from queue, processed them and broadcast them
    while (true) {
        /*ActionMove *action = dynamic_cast<ActionMove*>(queue->pop());
        if (action->getType() == UPDATE) {  //  El tipo movimiento que recibo
            ActionUpdate *actionUpdate = dynamic_cast<ActionUpdate *>(action);
            std::cout << "Game " << gameName << " received update: " << actionUpdate->getGameName() << std::endl;

         */
    }
    // ActionMove *action = dynamic_cast<ActionMove*>(queue->pop());
}

bool Game::isFull() const {
    return playerOnLine == capacity;
}

ProtectedQueue<Action *> * Game::getQueue() {
    return queue;
}

void Game::stop() {}

void Game::broadcastUpdate(Action *update) {
    for (auto & sender : mapSender) {
        sender.second->push(update);
    }
}

void Game::brodcastUpdateGameEvents(std::vector<Action *> updates) {
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
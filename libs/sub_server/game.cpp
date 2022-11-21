//
// Created by lucaswaisten on 04/11/22.
//

#include "game.h"
#include "sub_common/Action.h"
#include "sub_common/ActionUpdate.h"

Game::Game(uint8_t capacity,
           std::string  name,
           BlockingQueue<Action *> *pQueue) :
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
        start();
        // broadcast new update with right id to the client
        std::string mensaje = "OWN";
        ActionUpdate *update = new ActionUpdate(id, mensaje); //creacion de partida, devuelve el id
        broadcastUpdate(update, id);
    }
}

void Game::run() {

}

bool Game::isFull() const {
    return playerOnLine == capacity;
}

BlockingQueue<Action *> * Game::getQueue() {
    return queue;
}

void Game::stop() {}

void Game::broadcastUpdate(Action *update, uint8_t id) {
    auto it = mapSender.find(id);
    if (it != mapSender.end()){
        it->second->push(update);
    }
}

void Game::broadcastUpdate(Action *update) {
    for (auto & sender : mapSender) {
        sender.second->push(update);
    }
}

void Game::brodcastUpdates(std::vector<Action *> updates) {
    for (auto & sender : mapSender) {
        for (auto & update : updates) {
            sender.second->push(update);
        }
    }
}

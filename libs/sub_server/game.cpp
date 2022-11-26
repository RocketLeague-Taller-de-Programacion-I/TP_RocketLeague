//
// Created by lucaswaisten on 04/11/22.
//

#include "game.h"

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
        running = true;
        start();

    }
}

void Game::run() {
/*
    std::vector<uint8_t> matchInfo = this->match.matchInfo();
    ServerUpdateWorld * update = new ServerUpdateWorld(id, matchInfo);
       broadcastUpdateGameEvents(update);
     *


    while (running) {

    }
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

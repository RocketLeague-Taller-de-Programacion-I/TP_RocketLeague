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

std::vector<uint8_t> Game::information() {
    //data: online,max,sizeName,name
    std::vector<uint8_t> data;
    data.push_back(playerOnLine);
    data.push_back(capacity);
    data.push_back(gameName.size());
    data.insert(data.end(), gameName.begin(), gameName.end());
    return data;
}
void Game::joinPlayer(uint8_t& id, BlockingQueue<ServerUpdate *> *sender) {
    playerOnLine++;
    mapSender.insert(std::pair<uint8_t ,BlockingQueue<ServerUpdate*>*>(id, sender));
    if (playerOnLine == capacity){
        running = true;
        uint16_t returnCode = OK;
        ServerUpdate *update = new ServerStartedGameACK(id, returnCode);
        broadcastUpdate(update);
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

void Game::stop() {}

Game::~Game() {
    for (auto & sender : mapSender) {
        delete sender.second;
    }
    join();
}

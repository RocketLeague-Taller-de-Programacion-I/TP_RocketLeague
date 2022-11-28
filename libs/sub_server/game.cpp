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
        uint8_t idD =0 , direction = 5;
        bool state = false;
        ServerAction *action = new ServerActionMove(idD, direction, state);
        queue->push(action);
        //  start();
    }
}

void Game::run() {
    // ActionMove cline [1, RIGHT, on]
    // ActionMove cline  [2, LEFT, off]
    std::cout << "Game " << gameName << " started" << std::endl;
    ServerAction *action;
    while (!queue->tryPop(action)) {
    }
    action->execute(match);
    match.step();
    std::vector<int> info = match.info();
    std::vector<uint8_t> dummy;
    uint8_t id = 0, returnCode = OK;
    ServerUpdate* update = new ServerUpdateWorld(id, returnCode, dummy , info);
    broadcastUpdate(update);
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

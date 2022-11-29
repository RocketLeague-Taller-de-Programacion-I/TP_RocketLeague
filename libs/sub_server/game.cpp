//
// Created by lucaswaisten on 04/11/22.
//

#include "game.h"

Game::Game(int capacity,
           std::string  name,
           ProtectedQueue<std::shared_ptr<ServerAction>> *pQueue) :
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
void Game::joinPlayer(uint8_t& id, BlockingQueue<std::shared_ptr<ServerUpdate>> *sender) {
    playerOnLine++;
    mapSender.insert(std::pair<uint8_t ,BlockingQueue<std::shared_ptr<ServerUpdate>>*>(id, sender));
    uint8_t direction = 5;
    bool state = false;
    match.addPlayer(id);
    std::shared_ptr<ServerAction> action = std::make_shared<ServerActionMove>(id, direction, state);
    queue->push(action);
    if (playerOnLine == capacity){
        start();
    }
}

void Game::run() {
    // ActionMove cline [1, RIGHT, on]
    // ActionMove cline  [2, LEFT, off]
    std::cout << "Game " << gameName << " started" << std::endl;
    std::shared_ptr<ServerAction> action;
    while (!queue->tryPop(action)) {
    }
    action->execute(match);
    match.step();
    std::vector<int> info = match.info();
    std::vector<uint8_t> dummy;
    uint8_t id = 0, returnCode = OK;
    std::shared_ptr<ServerUpdate> update = std::make_shared<ServerUpdateWorld>(id, returnCode, dummy , info);
    //ServerUpdate* update = new ServerUpdateWorld(id, returnCode, dummy , info);
    broadcastUpdate(update);
}

bool Game::isFull() const {
    return playerOnLine == capacity;
}

ProtectedQueue<std::shared_ptr<ServerAction>> * Game::getQueue() {
    return queue;
}

void Game::broadcastUpdate(const std::shared_ptr<ServerUpdate>& update) {
    for (auto & sender : mapSender) {
        sender.second->push(const_cast<std::shared_ptr<ServerUpdate> &>(update));
    }
}

/*void Game::brodcastUpdateGameEvents(std::vector<ServerUpdate *> updates) {
    for (auto & sender : mapSender) {
        for (auto & update : updates) {
            sender.second->push(update);
        }
    }
}*/

void Game::stop() {}

Game::~Game() {
    for (auto & sender : mapSender) {
        delete sender.second;
    }
    join();
}

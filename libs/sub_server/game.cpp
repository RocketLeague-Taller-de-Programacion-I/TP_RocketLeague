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
        queue(pQueue),
        finished(false){}

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
   std::cout << "Game " << gameName << " started" << std::endl;
    std::shared_ptr<ServerAction> action;
    while (not finished) {
        //check if time of match's usleep reached 3 minutes
        //TODO: check if clientManager are still alive

        if (match.isFinished()){
            finished = true;
            break;
        }
        if (queue->tryPop(action) and action){
            action->execute(match); //update model
        }
        match.step(); //update box2d
        std::vector<int> info = match.info();
        uint8_t id = 0, returnCode = OK;
        std::vector<uint8_t> dummy;
        std::shared_ptr<ServerUpdate> update = std::make_shared<ServerUpdateWorld>(id, returnCode, dummy , info);
        broadcastUpdate(update);
    }

    std::cout << "Game " << gameName << " finished" << std::endl;
}

bool Game::isFull() const {
    return playerOnLine == capacity;
}

bool Game::isFinished() const {
    return finished;
}

ProtectedQueue<std::shared_ptr<ServerAction>> * Game::getQueue() {
    return queue;
}

void Game::broadcastUpdate(const std::shared_ptr<ServerUpdate>& update) {
    for (auto & sender : mapSender) {
        sender.second->push(const_cast<std::shared_ptr<ServerUpdate> &>(update));
    }
}

bool Game::hasPlayer(uint8_t idPlayer) {
    return mapSender.find(idPlayer) != mapSender.end();
}

void Game::deletePlayer(uint8_t idPlayer) {
    mapSender.erase(idPlayer);
    playerOnLine--;
    finished = (playerOnLine == 0);
}

void Game::stop() {
    finished = true;
    delete queue;
    join();
}

Game::~Game() {}


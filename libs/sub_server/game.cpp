//
// Created by lucaswaisten on 04/11/22.
//

#include "game.h"
#include "sub_server/server_updates/ServerUpdateStats.h"

Game::Game(int capacity,
           std::string  name,
           ProtectedQueue<std::shared_ptr<ServerAction>> *pQueue) :
        match(name, capacity),
        capacity(capacity),
        playerOnLine(0),
        gameName(std::move(name)),
        queue(pQueue),
        finished(false),
        gameStarted(false){}

std::vector<uint8_t> Game::information() {
    //data: online,max,sizeName,name
    std::vector<uint8_t> data;
    data.push_back(playerOnLine);
    data.push_back(capacity);
    data.push_back(gameName.size());
    data.insert(data.end(), gameName.begin(), gameName.end());
    return data;
}
void Game::joinPlayer(uint8_t& id, BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>> *sender) {
    playerOnLine++;
    mapSender.insert(std::pair<uint8_t ,BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>>*>(id, sender));
    match.addPlayer(id);
    if (playerOnLine == capacity){
        start();
    }
}

void Game::run() {
   std::cout << "Game " << gameName << " started" << std::endl;
    std::shared_ptr<ServerAction> action;
    while (not finished) {
        if (match.isFinished()){
            finished = true;
            break;
        }
        if (queue->tryPop(action) and action){
            action->execute(match); //update model
        }
        match.step(); //update box2d
        std::vector<int> info = match.info();
        std::optional<std::shared_ptr<ServerUpdate>> update = std::make_shared<ServerUpdateWorld>(info);
        broadcastUpdate(update);
    }
    std::cout << "Game " << gameName << " finished" << std::endl;
    std::vector<int> stats = match.stats();
    std::optional<std::shared_ptr<ServerUpdate>> update = std::make_shared<ServerUpdateStats>(stats);
    broadcastUpdate(update);
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

void Game::broadcastUpdate(std::optional<std::shared_ptr<ServerUpdate>> &update) {
    for (auto & sender : mapSender) {
        //if sender is null then the client disconnected
        if (sender.second) {
            sender.second->push(update);
        }
    }
}

bool Game::hasPlayer(uint8_t idPlayer) {
    return mapSender.find(idPlayer) != mapSender.end();
}

void Game::deletePlayer(uint8_t idPlayer) {
    mapSender.erase(idPlayer);
    match.removePlayer(idPlayer);
    playerOnLine--;
    finished = (playerOnLine == 0);
}

void Game::stop() {
    finished = true;
    delete queue;
}

Game::~Game() {
    this->match.deleteMatch();
}


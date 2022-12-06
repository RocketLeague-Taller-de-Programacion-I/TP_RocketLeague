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
    std::shared_ptr<ServerAction> action;
    ProtectedQueueBounded<std::optional<std::shared_ptr<ServerUpdate>>> queueBounded(500);

    while (not finished) {
        if (match.isFinished()){
            finished = true;
            break;
        }
        if (queue->tryPop(action) and action){
            action->execute(match); //update model
        }
        if(match.step()) { //update box2d and check if there were any goals made
            broadcastUpdateForRepetition(queueBounded);
        }
        std::vector<int> info = match.info();
        std::optional<std::shared_ptr<ServerUpdate>> update = std::make_shared<ServerUpdateWorld>(info);
        broadcastUpdate(update);
        //push last update also to this queue to have a repeteiton
        queueBounded.push(update);
    }
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

void Game::broadcastUpdateForRepetition(ProtectedQueueBounded<std::optional<std::shared_ptr<ServerUpdate>>> &bounded) {
    std::optional<std::shared_ptr<ServerUpdate>> update;
    while (bounded.tryPop(update)){
        usleep(USECONDS_TO_SLEEP);
        broadcastUpdate(update);
    }
}

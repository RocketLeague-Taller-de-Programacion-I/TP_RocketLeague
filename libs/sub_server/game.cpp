//
// Created by lucaswaisten on 04/11/22.
//

#include "game.h"
#include <utility>

std::string Game::information() {
    return "";
}


void Game::joinPlayer(uint8_t i, BlockingQueue<Action*> *sender) {
    playerOnLine++;
    mapSender.insert(std::pair<uint8_t ,BlockingQueue<Action*>*>(i,sender));
    if (playerOnLine == capacity){
        start();
    }
}
void Game::run() {
    do {
        auto action = queue->pop();
        std::function<void(uint8_t&,uint8_t&)> setMove
                = [this](uint8_t & id, uint8_t & move){return this->match.movement(id,move); };
        action->execute(setMove);
    } while (not closed);
}

bool Game::isFull() const {
    return playerOnLine == capacity;
}


BlockingQueue<Action *> * Game::getQueue() {
    return queue;
}

void Game::stop() {}

Game::Game(uint8_t &aCapacity,
           const std::string &aName,
           BlockingQueue<Action *> *pQueue) :
           match(aName,aCapacity),
           capacity(aCapacity),
           playerOnLine(0),
           gameName(aName),
           closed(false),
           queue(pQueue) {}

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

}

bool Game::isFull() const {
    return playerOnLine == capacity;
}

Game::Game(uint8_t capacity,
           std::string  name,
           BlockingQueue<Action *> *pQueue) :
           capacity(capacity),
           playerOnLine(0),
           gameName(std::move(name)),
           queue(pQueue) {}

BlockingQueue<Action *> * Game::getQueue() {
    return queue;
}

void Game::stop() {}

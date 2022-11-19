//
// Created by lucaswaisten on 04/11/22.
//

#include "game.h"
#include <utility>

std::string Game::information() {
    return "";
}
/*
Game::Game(uint8_t aCant,
           std::string aName) :
           capacity(aCant),
           playerOnLine(0),
           gameName(std::move(aName)) {}*/

void Game::joinPlayer(uint8_t i, BlockingQueue<Update> *sender) {
    playerOnLine++;
   // mapReceiver.insert(std::pair<uint8_t ,BlockingQueue<Action>&>(i,receiver));
    mapSender.insert(std::pair<uint8_t ,BlockingQueue<Update>*>(i,sender));
}
void Game::run() {

}

bool Game::isFull() const {
    return playerOnLine == capacity;
}
/*
Game::Game(uint8_t i, std::string basicString, BlockingQueue<Action> &queue) :
                    capacity(i),
                    gameName(basicString),
                    queue(queue){}*/

Game::Game(uint8_t capacity,
           std::string  name,
           BlockingQueue<Action> *pQueue) :
           capacity(capacity),
           playerOnLine(0),
           gameName(std::move(name)),
           queue(pQueue) {}

BlockingQueue<Action> *Game::getQueue() {
    return queue;
}

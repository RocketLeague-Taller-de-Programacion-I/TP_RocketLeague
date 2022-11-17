//
// Created by lucaswaisten on 04/11/22.
//

#include "game.h"
#include <utility>
/*
bool Game::joinPlayer() {
    if (playerOnLine == capacity)
        return false;
    playerOnLine++;
    return true;
}*/

std::string Game::information() {
    return "";
}

Game::Game(uint8_t aCant,
           std::string aName) :
           capacity(aCant),
           playerOnLine(0),
           gameName(std::move(aName)) {}

void Game::joinPlayer(uint8_t i, BlockingQueue<Action> &receiver, BlockingQueue<Update> &sender) {
    playerOnLine++;
    mapReceiver.insert(std::pair<uint8_t ,BlockingQueue<Action>&>(i,receiver));
    mapSender.insert(std::pair<uint8_t ,BlockingQueue<Update>&>(i,sender));
}
void Game::run() {

}

bool Game::isFull() const {
    return playerOnLine == capacity;
}

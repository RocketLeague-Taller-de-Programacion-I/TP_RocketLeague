//
// Created by lucaswaisten on 04/11/22.
//

#include "game.h"

#include <utility>

bool Game::joinPlayer() {
    if (playerOnLine == capacity)
        return false;
    playerOnLine++;
    return true;
}

std::string Game::information() {
    return "";
}

Game::Game(uint8_t aCant,
           std::string aName) :
           capacity(aCant),
           playerOnLine(1),
           gameName(std::move(aName)) {}

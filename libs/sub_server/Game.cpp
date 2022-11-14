//
// Created by franco on 13/11/22.
//

#include "Game.h"

#include <utility>
Game::Game(const b2World& world, std::string &name, int &playersRequired) : world(world), playersRequired(playersRequired), goalsLocal(0), goalsVisit(0), ball(&this->world, 1.0), name(std::move(name)) {
}


bool Game::complete() const {
    if (playersRequired == playersConnected) { return true; }
    return false;
}

int Game::addPlayer(std::string &clientName) {
    if (complete()) {
        return 1;
    }
    this->playersConnected++;
    Car car(&this->world);
    std::pair<std::map<std::string,Car>::iterator,bool> ret;

    ret = players.insert(std::pair<std::string,
            Car>(clientName,
                      car));
    if (complete()) {
        std::cout << "Comenzando partida " <<
        this->name << "..." <<
        std::endl;
    }
    return 0;
}
void Game::updateGame() {

}
Game::~Game() { }
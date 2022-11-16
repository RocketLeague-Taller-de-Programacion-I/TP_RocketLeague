//
// Created by franco on 16/11/22.
//

#include "Match.h"

#include <utility>

Match::Match(std::string gameName, int required) : name(std::move(gameName)), playersRequired(required), playersConnected(0), world(b2World(b2Vec2(0,-9.8))) {
}

void Match::addPlayer(std::string &name) {
    Car car(&this->world);
    std::pair<std::map<std::string,Car>::iterator,bool> ret;
    ret = this->players.insert( std::pair<std::string,Car>(name,car));
    this->playersConnected++;
}

Match::~Match() { }

void Match::update() {}
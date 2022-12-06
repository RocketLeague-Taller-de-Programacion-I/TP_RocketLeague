//
// Created by franco on 28/11/22.
//

#include "ClientUpdateWorld.h"

Ball ClientUpdateWorld::getBall() {
    return ball;
}

std::vector<Car> ClientUpdateWorld::getCars() {
    return cars;
}

Score ClientUpdateWorld::getScore() {
    return score;
}

GameTime ClientUpdateWorld::getTime() {
    return gameTime;
}

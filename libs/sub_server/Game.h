//
// Created by franco on 13/11/22.
//

#ifndef ROCKETLEAGUE_GAME_H
#define ROCKETLEAGUE_GAME_H


#include <map>
#include "box2d/b2_world.h"
#include "Car.h"
#include "Ball.h"

class Game {
 private:
    b2World world;
    b2Vec2 gravity;
    int playersRequired;
    int playersConnected;
    int goalsLocal;
    int goalsVisit;
    std::string name;
    std::map<std::string, Car> players;
    std::map<std::string, Car> goalers;
    std::map<std::string, Car> assitants;
    Ball ball;
 public:
    Game(const b2World& world, std::string &name, int &playersRequired);
    int addPlayer(std::string &name);
    bool complete() const;
    ~Game();

    void updateGame();
};


#endif //ROCKETLEAGUE_GAME_H

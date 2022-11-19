//
// Created by franco on 16/11/22.
//

#ifndef ROCKETLEAGUE_MATCH_H
#define ROCKETLEAGUE_MATCH_H


#include <map>
#include "box2d/box2d.h"
#include "Car.h"

class Match {
private:
    std::string name;
    b2World world;
    std::map<std::string, Car> players;
    std::map<std::string, Car> scorers;
    std::map<std::string, Car> assistants;
    int playersConnected;
    int playersRequired;
public:
    Match(std::string name, int required);
    ~Match();
    void update();

    void addPlayer(std::string &name);

    float carsInfo();

    void moveRight(std::string &basicString);

    float info();
};


#endif //ROCKETLEAGUE_MATCH_H

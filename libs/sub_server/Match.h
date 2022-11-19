//
// Created by franco on 16/11/22.
//

#ifndef ROCKETLEAGUE_MATCH_H
#define ROCKETLEAGUE_MATCH_H


#include <map>
#include "box2d/box2d.h"
#include "Car.h"
#include "MyContactListener.h"

/*  User data:
    0 -> nullptr
    1 -> Ground
    2 -> Ball
    3 -> Car
 */

class Match {
private:
    std::string name;
    b2World world;
    std::map<std::string, Car> players;
    std::map<std::string, Car> scorers;
    std::map<std::string, Car> assistants;
    b2Body* staticBody; //  Floor
    int playersConnected;
    int playersRequired;
    MyContactListener collisionListener;
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

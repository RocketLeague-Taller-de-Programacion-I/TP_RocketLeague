//
// Created by franco on 16/11/22.
//

#ifndef ROCKETLEAGUE_MATCH_H
#define ROCKETLEAGUE_MATCH_H


#include <map>
#include <memory>
#include "box2d/box2d.h"
#include "Car.h"
#include "MyContactListener.h"
#include "Ball.h"

class Match {
private:
    std::string name;
    b2World world;
    Ball* ball;
    std::map<int, Car*> players;
    std::map<int, Car*> scorers;
    std::map<int, Car*> assistants;
    int playersConnected;
    int playersRequired;
    int goalsLocal;
    int goalsVisit;
    b2Body* staticBody;
    b2FixtureDef fixDef;
    std::unique_ptr<MyFixtureUserDataType> myUserData;
    MyContactListener listener;
public:
    Match(std::string name, int required);
    ~Match();
    void update();

    void addPlayer(int &id);

    float carsInfo();

    void moveRight(int &id);

    float info();

    void moveLeft(int &id);

    void jump(int &id);

    void checkGoals();
};


#endif //ROCKETLEAGUE_MATCH_H

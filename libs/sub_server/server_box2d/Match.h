//
// Created by franco on 16/11/22.
//

#ifndef ROCKETLEAGUE_MATCH_H
#define ROCKETLEAGUE_MATCH_H


#include <map>
#include <memory>
#include <functional>

#include "box2d/box2d.h"

#include "Car.h"
#include "Ball.h"
#include "MyContactListener.h"

#include "../server_updates/ServerUpdate.h"

#define USECONDS_TO_SLEEP 6000
#define TIME_TO_PLAY 180000000
#define BX2D_TIMESTEP 0.006f
#define BX2D_VELOCITY_ITERATIONS 8
#define BX2D_POSITION_ITERATIONS 3

class Match {
private:
    std::string name;
    b2World world;
    Ball* ball;
    std::map<uint8_t, Car*> players;
    std::map<uint8_t, Car*> scorers;
    std::map<uint8_t, Car*> assistants;
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
    void addPlayer(uint8_t &id);

    void moveRight(uint8_t  &id, bool state);
    std::vector<int> info();

    void moveLeft(uint8_t &id, bool state);

    void jump(uint8_t &id, bool state);
    void checkGoals();
    void step();
    int visit();
    int local();
    void turbo(uint8_t &id, bool state);

    unsigned int timeElapsed = 0;

    bool isFinished();
};


#endif //ROCKETLEAGUE_MATCH_H
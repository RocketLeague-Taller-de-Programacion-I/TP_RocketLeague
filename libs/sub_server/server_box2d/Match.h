//
// Created by franco on 16/11/22.
//

#ifndef ROCKETLEAGUE_MATCH_H
#define ROCKETLEAGUE_MATCH_H


#include <map>
#include <memory>
#include <functional>

#include "box2d/box2d.h"

#include "sub_server/server_box2d/Car.h"
#include "MyContactListener.h"
#include "sub_server/server_box2d/Ball.h"

#include "sub_server/server_updates/ServerUpdate.h"

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
    void moveRight(uint8_t  &id, std::function<void(ServerUpdate* )> function);
    void info();
    void moveLeft(uint8_t &id, std::function<void(ServerUpdate* )> function);
    void jump(uint8_t &id, std::function<void(ServerUpdate* )> function);
    void checkGoals();
    void step();
    int visit();
    int local();
    std::vector<uint8_t> ballInfo();
    std::vector<uint8_t> scoreInfo();
    std::vector<uint8_t> matchUpdate();
    std::vector<uint8_t> matchInfo();
};


#endif //ROCKETLEAGUE_MATCH_H
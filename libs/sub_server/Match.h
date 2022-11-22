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
#include "MyContactListener.h"
#include "Ball.h"
#include "../sub_common/sub_action/ActionUpdate.h"


class Match {
private:
    std::string name;
    b2World world;
    Ball* ball;
    std::map<uint8_t , Car*> players;
    std::map<uint8_t , Car*> scorers;
    std::map<uint8_t , Car*> assistants;
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
    float carsInfo();
    void moveRight(uint8_t &id, std::function<void(ActionUpdate * )> function);
    void info();
    void moveLeft(uint8_t &id, std::function<void(ActionUpdate * )> function);
    void jump(uint8_t &id, std::function<void(ActionUpdate * )> function);
    void checkGoals();
    void step();
    void updateGame(uint8_t &id);
    int visit();
    int local();

    std::vector<int> ballInfo();
};


#endif //ROCKETLEAGUE_MATCH_H

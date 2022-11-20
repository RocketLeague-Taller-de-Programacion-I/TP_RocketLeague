//
// Created by franco on 16/11/22.
//

#ifndef ROCKETLEAGUE_MATCH_H
#define ROCKETLEAGUE_MATCH_H


#include <map>
#include <memory>
#include "box2d/box2d.h"
#include "Car.h"
#include "sub_common/sub_action/ActionUpdate.h"

class Match {
private:
    std::string name;
    b2World world;
    std::map<std::string, Car*> players;
    std::map<std::string, Car*> scorers;
    std::map<std::string, Car*> assistants;
    int playersConnected;
    int playersRequired;
    b2Body* staticBody;
    b2FixtureDef fixDef;
    std::unique_ptr<MyFixtureUserDataType> myUserData;
public:
    Match(std::string name, int required);
    ~Match();
    void update();

    void addPlayer(std::string &string);

    float carsInfo();

    void moveRight(std::string &basicString);

    float info();

    void movement(uint8_t &id, uint8_t &typeMove);

    void moveDown(uint8_t &id, std::function<void(ActionUpdate *)> updateClientSender);
    void moveRight(uint8_t &id, std::function<void(ActionUpdate *)> updateClientSender);
    void moveLeft(uint8_t &id, std::function<void(ActionUpdate *)> updateClientSender);
    void moveUp(uint8_t &id, std::function<void(ActionUpdate *)> updateClientSender);
    void moveJump(uint8_t &id, std::function<void(ActionUpdate *)> updateClientSender);
    void moveTurbo(uint8_t &id, std::function<void(ActionUpdate *)> updateClientSender);

};


#endif //ROCKETLEAGUE_MATCH_H

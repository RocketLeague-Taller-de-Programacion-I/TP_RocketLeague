//
// Created by franco on 16/11/22.
//

#include "Match.h"
#include "sub_server/server_actions/ServerAction.h"

#include <utility>
#include <list>
#include <unistd.h>
#include <memory>

#define LOCALGOAL (0.005)
#define VISITGOAL  (40.000)
#define GOALSIZE 1.5
#define BALL 0x0002
#define CAR 0x0003
#define GROUND 0x0004
Match::Match(std::string gameName, int required) : name(std::move(gameName)), world(b2World(b2Vec2(0,-10))), playersConnected(0), playersRequired(required), goalsLocal(0), goalsVisit(0) {
    world.SetContactListener(&this->listener);
    myUserData = std::make_unique<MyFixtureUserDataType>();
    fixDef.userData.pointer = reinterpret_cast<uintptr_t>(myUserData.get());
    myUserData->mObjectType = 1;  //  Floor
    //a static body -> Cancha
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0, 0);
    staticBody = world.CreateBody(&myBodyDef);
    b2PolygonShape polygonShape;
    fixDef.shape = &polygonShape;
    fixDef.restitution = 0.5;
    polygonShape.SetAsBox( 20, 0.5, b2Vec2(20, 0), 0);  //ground
    myUserData->mOwningFixture = staticBody->CreateFixture(&fixDef);
    fixDef.filter.groupIndex = GROUND;
    myUserData->mOwningFixture->SetFilterData(fixDef.filter);
    //  Balls creation
    this->ball = new Ball(&this->world, 1);
}


void Match::addPlayer(uint8_t &id) {
    this->players[id] = new Car(&this->world, id);
    this->playersConnected++;
}

void Match::removePlayer(uint8_t &id) {
    this->players.erase(id);
    this->playersConnected--;
}

void Match::step() {
    for ( std::pair<const uint8_t,Car*> &player : players){
        player.second->update();
    }
    checkGoals();
    this->world.Step(BX2D_TIMESTEP, BX2D_VELOCITY_ITERATIONS, BX2D_POSITION_ITERATIONS);
    usleep(USECONDS_TO_SLEEP);
    timeElapsed += USECONDS_TO_SLEEP;
}

void Match::moveRight(uint8_t &id, bool state) {
    if(state == ON) {
        this->players.at(id)->startMovingRight();
    } else {
        this->players.at(id)->stopMovingRight();
    }
}

std::vector<int> Match::info() {
    std::vector<int> data;
    //    bola -> 4bytes
    uint16_t x = (uint16_t) (this->ball->X() * 1000);
    data.push_back(x);
    uint16_t y = (uint16_t) (this->ball->Y() * 1000);
    data.push_back(y);
//    score -> 4bytes
    data.push_back((this->goalsLocal));
    data.push_back((this->goalsVisit));
//    numero de clientes 2 bytes
    data.push_back((this->playersConnected));
//    tiempo restante
    uint16_t time = (TIME_TO_PLAY - timeElapsed)/1000000;
    data.push_back(time);
//    cliente 7bytes
    for ( auto &player : players){
        uint16_t  id = (uint16_t) player.first;
        data.push_back((id));
        auto carX = (uint16_t) (player.second->X() * 1000);
        data.push_back((carX));
        auto carY = (uint16_t) (player.second->Y() * 1000);
        data.push_back((carY));
        uint16_t angle = (uint16_t) abs(player.second->angleDeg() * 1000);
        // get sign bit from angle
        uint8_t sign = (player.second->angleDeg() < 0) ? 1 : 0;
        uint8_t facing = player.second->facingWhere();
        data.push_back((sign));
        data.push_back((angle));
        data.push_back(facing);
    }
    return data;
}

void Match::moveLeft(uint8_t &id, bool state) {
    if(state == ON) {
        this->players.at(id)->startMovingLeft();
    } else {
        this->players.at(id)->stopMovingLeft();
    }
}
void Match::jump(uint8_t &id, bool state) {
    if(state == ON) {
        this->players.at(id)->jump();
    }
}
void Match::turbo(uint8_t &id, bool state) {
    if(state == ON) {
        this->players.at(id)->turbo();
    }
}

void Match::checkGoals() {
    if (this->ball->X() <= LOCALGOAL and this->ball->Y() <= GOALSIZE) {  //  LOCALGOAL es el arco del local
        this->goalsVisit++;
        this->ball->restartGame();
    }
    else if (this->ball->X() >= VISITGOAL and this->ball->Y() <= GOALSIZE) {  //  VISITGOAL es el arco del visitante
        this->goalsLocal++;
        this->ball->restartGame();
    }
}
int Match::local() {
    return this->goalsLocal;
}
int Match::visit() {
    return this->goalsVisit;
}
bool Match::isFinished() {
    return timeElapsed >= (unsigned int)TIME_TO_PLAY;
}

Match::~Match() {
    for ( std::pair<const uint8_t,Car*> &player : players){
        delete player.second;
        player.second = nullptr;
    }
    delete this->ball;
}

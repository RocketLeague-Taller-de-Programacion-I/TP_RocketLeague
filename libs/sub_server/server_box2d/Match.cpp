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
Match::Match(std::string gameName, int required) : name(std::move(gameName)), world(b2World(b2Vec2(0,-10))), playersConnected(0), playersRequired(required), goalsLocal(0), goalsVisit(0),
                                                   listener(contacts) {
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
    int x = (int) (this->ball->X() * 1000);
    data.push_back(x);
    int y = (int) (this->ball->Y() * 1000);
    data.push_back(y);
    int signBall = (ball->angleDeg() < 0) ? 1 : 0;
    int angleBall = (int) abs(ball->angleDeg() * 1000);
    data.push_back(signBall);
    data.push_back(angleBall);
//    score -> 4bytes
    data.push_back((this->goalsLocal));
    data.push_back((this->goalsVisit));
//    numero de clientes 2 bytes
    data.push_back((this->playersConnected));
//    tiempo restante
    int time = (TIME_TO_PLAY - timeElapsed)/1000000;
    data.push_back(time);
//    cliente 7bytes
    for ( auto &player : players){
        int  id = (int) player.first;
        data.push_back((id));
        int carX = (int) (player.second->X() * 1000);
        data.push_back((carX));
        int carY = (int) (player.second->Y() * 1000);
        data.push_back((carY));

        int sign = (player.second->angleDeg() < 0) ? 1 : 0;
        int angle = (int) abs(player.second->angleDeg() * 1000);
        int facing = player.second->facingWhere();

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
        addGoalToScorer();
    }
    else if (this->ball->X() >= VISITGOAL and this->ball->Y() <= GOALSIZE) {  //  VISITGOAL es el arco del visitante
        this->goalsLocal++;
        this->ball->restartGame();
        addGoalToScorer();
    }
}
int Match::local() const {
    return this->goalsLocal;
}
int Match::visit() const {
    return this->goalsVisit;
}
bool Match::isFinished() const {
    return timeElapsed >= (unsigned int)TIME_TO_PLAY;
}

Match::~Match() {}

void Match::addGoalToScorer() {
    uint8_t id = this->contacts.back();
    auto search = this->scorers.find(id);
    if (search != scorers.end()) {
        scorers[id] = scorers[id]+1;
    } else {
        scorers[id] = 1;
    }
}
std::vector<int> Match::stats() {
    std::vector<int> stats;
    uint8_t players = this->scorers.size();
    stats.emplace_back(players);
    for (std::pair<const uint8_t,int> &scorer : scorers) {
        uint8_t id = scorer.first;
        uint8_t goals = scorer.second;
        stats.emplace_back(id);
        stats.emplace_back(goals);
    }
    return stats;
}

void Match::deleteMatch() {
    for ( auto &player : players){
        delete player.second;
    }
    players.clear();
    delete this->ball;
}
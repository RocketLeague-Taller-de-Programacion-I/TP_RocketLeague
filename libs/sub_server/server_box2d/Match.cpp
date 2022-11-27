//
// Created by franco on 16/11/22.
//

#include "Match.h"

#include <utility>
#include <list>
#include <unistd.h>
#include <memory>

#define LOCALGOAL (-37.985)
#define VISITGOAL  (37.985)
#define GOALSIZE 5

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
    polygonShape.SetAsBox( 40, 0.5, b2Vec2(0, 0), 0);//ground
    myUserData->mOwningFixture = staticBody->CreateFixture(&fixDef);
    fixDef.friction = 0.2;
    //  Creo ball
    this->ball = new Ball(&this->world, 0.7);
}


void Match::addPlayer(uint8_t &id) {
    this->players[id] = new Car(&this->world, id);
    this->playersConnected++;
}

Match::~Match() {
    for ( std::pair<const uint8_t,Car*> &player : players){
        delete player.second;
        player.second = nullptr;
    }
    delete this->ball;
}

void Match::step() {
    for ( std::pair<const uint8_t,Car*> &player : players){
        player.second->update();
    }
    this->world.Step(0.15, 42, 3);
    usleep(0.015*1000000);
    //  enviar a todos los clientes la respuesta
}

void Match::moveRight(uint8_t &id, std::function<void(ServerUpdate* )> function) {
    this->players.at(id)->startMovingRight();
    // update
}
void Match::info() {
}
void Match::moveLeft(uint8_t &id, std::function<void(ServerUpdate* )> function) {
    this->players.at(id)->startMovingLeft();
}
void Match::jump(uint8_t &id, std::function<void(ServerUpdate* )> function) {
    this->players.at(id)->jump();
}
void Match::checkGoals() {
    if (this->ball->X() <= LOCALGOAL && this->ball->Y() <= GOALSIZE) {  //  LOCALGOAL es el arco del local
        this->goalsVisit++;
        this->ball->restartGame();
    }
    else if (this->ball->X() >= VISITGOAL && this->ball->Y() <= GOALSIZE) {  //  VISITGOAL es el arco del visitante
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

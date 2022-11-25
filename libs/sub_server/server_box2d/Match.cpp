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
    //  Creo ball
    this->ball = new Ball(&this->world, 0.7);
}


void Match::addPlayer(uint8_t &id) {
    this->players[id] = new Car(&this->world, id);
    this->playersConnected++;
}

Match::~Match() {
    for ( std::pair<const uint8_t,Car*> &player : players){
        //Plaats *p = place.second;
        delete player.second;
        player.second = nullptr;
    }
    delete this->ball;
}

void Match::step() {
    this->world.Step(0.15, 42, 3);
    usleep(0.015*1000000);
    //  enviar a todos los clientes la respuesta
}

void Match::moveRight(uint8_t &id, std::function<void(ServerUpdate* )> function) {
    this->players.at(id)->goRight();
    // update
}
void Match::info() {
}
void Match::moveLeft(uint8_t &id, std::function<void(ServerUpdate* )> function) {
    this->players.at(id)->goLeft();
}
void Match::jump(uint8_t &id, std::function<void(ServerUpdate* )> function) {
    this->players.at(id)->jump();
}
void Match::checkGoals() {
    if (this->ball->X() <= LOCALGOAL) {  //  LOCALGOAL es el arco del local
        this->goalsVisit++;
        this->ball->restartGame();
    }
    else if (this->ball->X() >= VISITGOAL) {  //  VISITGOAL es el arco del visitante
        this->goalsLocal++;
        this->ball->restartGame();
    }
}
std::vector<uint8_t> Match::matchUpdate() {
    std::vector<uint8_t> toSend;
    for (auto &player : this->players) {
        toSend.emplace_back(player.second->getId());
        toSend.emplace_back(' ');
        toSend.emplace_back((player.second->X()));
        toSend.emplace_back(' ');
        toSend.emplace_back((player.second->Y()));
        toSend.emplace_back(' ');
        toSend.emplace_back((player.second->angleDeg()));
        toSend.emplace_back(',');
    }
    return toSend;
}
int Match::local() {
    return this->goalsLocal;
}
int Match::visit() {
    return this->goalsVisit;
}
std::vector<uint8_t> Match::ballInfo() {
    std::vector<uint8_t> toSend;
    uint8_t x = this->ball->X();
    uint8_t y = this->ball->Y();
    toSend.emplace_back(x);
    toSend.emplace_back(' ');
    toSend.emplace_back(y);
    toSend.emplace_back(',');
    return toSend;
}
// TODO: Match info
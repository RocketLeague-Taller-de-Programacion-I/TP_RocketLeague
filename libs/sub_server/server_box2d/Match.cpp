//
// Created by franco on 16/11/22.
//

#include "Match.h"
#include "sub_server/server_actions/ServerAction.h"

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

void Match::moveRight(uint8_t &id, bool state) {
    if(state == ON) {
        this->players.at(id)->startMovingRight();
    } else {
        this->players.at(id)->stopMovingRight();
    }
    // info(
}
// TODO: mover implementacion de bytes a protocolo o beSerizlized
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
//    cliente 7bytes
    for ( auto &player : players){
        uint16_t  id = (uint16_t) player.first;
        data.push_back((id));
        x = (uint16_t) (player.second->X() * 1000);
        data.push_back((x));

        y = (uint16_t) (player.second->Y() * 1000);
        data.push_back((y));

        uint16_t angle = (uint16_t) abs(player.second->angleDeg() * 1000);
        // get sign bit from angle
        uint8_t sign = (player.second->angleDeg() < 0) ? 1 : 0;
        data.push_back((sign));
        data.push_back((angle)); //  1er byte
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

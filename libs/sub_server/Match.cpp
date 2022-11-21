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

Match::Match(std::string gameName, int required) : name(std::move(gameName)), playersRequired(required), playersConnected(0), world(b2World(b2Vec2(0,-10))), goalsLocal(0), goalsVisit(0) {
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


void Match::addPlayer(int &id) {
    this->players[id] = new Car(&this->world);
    this->playersConnected++;
}

Match::~Match() {
    for ( std::pair<const int,Car*> &player : players){
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
float Match::carsInfo() {
   step();
   float carsConnected;
    for (auto& player : this->players) {
        //  cppcheck-suppress useStlAlgorithm
        carsConnected = (player.second->X());
    }

    return carsConnected;

}
void Match::moveRight(int &id, std::function<void(ActionUpdate * )> function) {
    this->players.at(id)->goRight();
    // update
}
void Match::info() {
}
void Match::moveLeft(int &id, std::function<void(ActionUpdate * )> function) {
    this->players.at(id)->goLeft();
}
void Match::jump(int &id, std::function<void(ActionUpdate * )> function) {
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
void Match::updateGame(int &id) {
}
int Match::local() {
    return this->goalsLocal;
}
int Match::visit() {
    return this->goalsVisit;
}
std::vector<int> Match::ballInfo() {
    std::vector<int> info;
    int x = this->ball->X();
    int y = this->ball->Y();
    info.emplace_back(x);
    info.emplace_back(y);
    return info;
}
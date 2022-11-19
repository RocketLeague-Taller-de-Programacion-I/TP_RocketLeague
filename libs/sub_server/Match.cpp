//
// Created by franco on 16/11/22.
//

#include "Match.h"

#include <utility>
#include <list>
#include <unistd.h>
#include <memory>

Match::Match(std::string gameName, int required) : name(std::move(gameName)), playersRequired(required), playersConnected(0), world(b2World(b2Vec2(0,-10))) {
    myUserData = std::make_unique<MyFixtureUserDataType>();
    fixDef.userData.pointer = reinterpret_cast<uintptr_t>(myUserData.get());
    myUserData->mObjectType = 1;  //  Floor
    //a static body
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0, 0);
    staticBody = world.CreateBody(&myBodyDef);
    b2PolygonShape polygonShape;
    fixDef.shape = &polygonShape;
    polygonShape.SetAsBox( 40, 0.5, b2Vec2(0, 0), 0);//ground
    myUserData->mOwningFixture = staticBody->CreateFixture(&fixDef);

    //shape definition


    //fixture definition





    //add four walls to the static body

}


void Match::addPlayer(std::string &name) {
    Car car(&this->world);
    std::pair<std::map<std::string,Car>::iterator,bool> ret;
    ret = this->players.insert( std::pair<std::string,Car>(name,car));
    this->playersConnected++;
}

Match::~Match() { }

void Match::update() {
    this->world.Step(0.15, 42, 3);
     usleep(0.015*1000000);
    //  enviar a todos los clientes la respuesta

}
float Match::carsInfo() {
    update();
    float carsConnected;
    for (auto& player : this->players) {
        //  cppcheck-suppress useStlAlgorithm
        carsConnected = (player.second.X());
    }
    return carsConnected;
}

void Match::moveRight(std::string &basicString) {
    Car car = this->players.at(basicString);
    car.goRight();
}
float Match::info() {

}

#include "Match.h"
#include "sub_server/server_actions/ServerAction.h"

#include <utility>
#include <list>
#include <unistd.h>
#include <memory>

#define GRAVITY (-10)
#define TIME_TO_PLAY 180000000

Match::Match(std::string gameName, int required) : name(std::move(gameName)), world(b2World(b2Vec2(0,GRAVITY))), playersConnected(0), playersRequired(required), goalsLocal(0), goalsVisit(0),
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
    std::shared_ptr<Ball> myBall = std::make_shared<Ball>(&this->world, RADIO);
    this->ball = myBall;
}


void Match::addPlayer(uint8_t &id) {
    std::shared_ptr<Car> car = std::make_shared<Car>(&this->world, id);
    this->players[id] = car;
    this->playersConnected++;
}

void Match::removePlayer(uint8_t &id) {
    this->players.erase(id);
    this->playersConnected--;
}
//retorns if there was a goal
bool Match::step() {
    bool goal = false;
    for ( std::pair<const uint8_t,std::shared_ptr<Car>> &player : players){
        player.second->update();
    }
    goal = checkGoals();
    this->world.Step(BX2D_TIMESTEP, BX2D_VELOCITY_ITERATIONS, BX2D_POSITION_ITERATIONS);
    usleep(USECONDS_TO_SLEEP);
    timeElapsed += USECONDS_TO_SLEEP;
    return goal;
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

bool Match::checkGoals() {
    bool goal = false;
    if (this->ball->X() <= LOCALGOAL and this->ball->Y() <= GOALSIZE) {  //  LOCALGOAL es el arco del local
        this->goalsVisit++;
        this->ball->restartGame();
        addGoalToScorer();
        goal = true;
    }
    else if (this->ball->X() >= VISITGOAL and this->ball->Y() <= GOALSIZE) {  //  VISITGOAL es el arco del visitante
        this->goalsLocal++;
        this->ball->restartGame();
        addGoalToScorer();
        goal = true;
    }
    return goal;
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
    players.clear();
}
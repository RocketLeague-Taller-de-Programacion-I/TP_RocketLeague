//
// Created by roby on 27/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTUPDATEWORLD_H
#define ROCKETLEAGUE_CLIENTUPDATEWORLD_H

#include "ClientUpdate.h"

class ClientUpdateWorld : public ClientUpdate {
private:
    Ball ball;
    Score score;
    std::vector<Car> cars;
public:
    ClientUpdateWorld(Ball &ball, Score &score, std::vector<Car> &cars) : ball(ball), score(score), cars(cars) {};
    ~ClientUpdateWorld() = default;

    uint8_t getType() const override { return WORLD; };
    Ball getBall() const { return ball; };
    Score getScore() const { return score; };
    std::vector<Car> getCars() const { return cars; };
};


#endif //ROCKETLEAGUE_CLIENTUPDATEWORLD_H

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
    Ball getBall() override;
    Score getScore() override;
    std::vector<Car> getCars() override;
};


#endif //ROCKETLEAGUE_CLIENTUPDATEWO
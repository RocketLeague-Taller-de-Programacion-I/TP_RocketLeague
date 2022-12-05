#ifndef ROCKETLEAGUE_CLIENTUPDATEWORLD_H
#define ROCKETLEAGUE_CLIENTUPDATEWORLD_H
#include "ClientUpdate.h"

class ClientUpdateWorld : public ClientUpdate {
private:
    Ball ball;
    Score score;
    GameTime gameTime;
    std::vector<Car> cars;
public:
    ClientUpdateWorld(Ball &ball, Score &score, GameTime &gameTime, std::vector<Car> &cars)
            : ball(ball), score(score), cars(cars), gameTime(gameTime) {};
    ~ClientUpdateWorld() = default;

    uint8_t getType() const override { return WORLD; };
    Ball getBall() override;
    Score getScore() override;
    GameTime getTime() override;
    std::vector<Car> getCars() override;
};


#endif //ROCKETLEAGUE_CLIENTUPDATEWO
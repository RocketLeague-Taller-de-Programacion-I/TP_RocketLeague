#ifndef ROCKETLEAGUE_BALL_H
#define ROCKETLEAGUE_BALL_H

#include <cstdint>

class Ball {
private:
    float x;
    float y;
    float angle;
public:
    Ball(float x, float y, float angle) : x(x), y(y), angle(angle) {};
    ~Ball() = default;

    float getX() const {
        return x;
    };
    float getY() const {
        return y;
    };
};


#endif //ROCKETLEAGUE_BALL_H

//
// Created by franco on 05/11/22.
//

#ifndef ROCKETLEAGUE_BALL_H
#define ROCKETLEAGUE_BALL_H

#include <cstdint>

class Ball {
private:
    uint16_t x;
    uint16_t y;
public:
    Ball(uint16_t x, uint16_t y) : x(x), y(y) {};
    ~Ball() = default;

    uint16_t getX() const { return x; };
    uint16_t getY() const { return y; };
};


#endif //ROCKETLEAGUE_BALL_H

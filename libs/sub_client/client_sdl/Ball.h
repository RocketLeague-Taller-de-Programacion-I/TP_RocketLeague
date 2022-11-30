//
// Created by franco on 05/11/22.
//

#ifndef ROCKETLEAGUE_BALL_H
#define ROCKETLEAGUE_BALL_H

#include <cstdint>
#define HEIGHT 600
#define PXM 37 //  Pixeles por metro
class Ball {
private:
    float x;
    float y;
public:
    Ball(float x, float y) : x(x * PXM), y(HEIGHT - (y * PXM)) {};
    ~Ball() = default;

    float getX() const { return x; };
    float getY() const { return y; };
};


#endif //ROCKETLEAGUE_BALL_H

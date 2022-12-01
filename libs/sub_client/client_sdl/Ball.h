//
// Created by franco on 05/11/22.
//

#ifndef ROCKETLEAGUE_BALL_H
#define ROCKETLEAGUE_BALL_H

#include <cstdint>

#define HEIGHT 600
#define PXM 37 //  Pixeles por metro

#define BALL_W_PX 55
#define BALL_H_PX 48

class Ball {
private:
    float x;
    float y;
public:
    Ball(float x, float y) : x(x), y(y) {};
    ~Ball() = default;

    float getX() const {
        return (x * PXM) - BALL_W_PX/2;
    };
    float getY() const {
        return HEIGHT - (y * PXM) - BALL_H_PX/2;
    };
};


#endif //ROCKETLEAGUE_BALL_H

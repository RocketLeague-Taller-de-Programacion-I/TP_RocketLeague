//
// Created by roby on 27/11/22.
//

#ifndef ROCKETLEAGUE_CAR_H
#define ROCKETLEAGUE_CAR_H


#include <cstdint>

class Car {
private:
    uint16_t x;
    uint16_t y;
    uint16_t sign;
    uint16_t angle;

public:
    Car(uint16_t &id, uint16_t x, uint16_t y, uint16_t sign, uint16_t angle) : x(x), y(y), sign(sign), angle(angle) {};
    ~Car() = default;

    //getters
    uint16_t getX() const { return x; };
    uint16_t getY() const { return y; };
    uint16_t getSign() const { return sign; };
    uint16_t getAngle() const { return angle; };
};


#endif //ROCKETLEAGUE_CAR_H
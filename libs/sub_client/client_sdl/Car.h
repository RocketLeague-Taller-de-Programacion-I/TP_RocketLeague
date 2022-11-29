//
// Created by roby on 27/11/22.
//

#ifndef ROCKETLEAGUE_CAR_H
#define ROCKETLEAGUE_CAR_H


#include <cstdint>

class Car {
private:
    uint16_t& id;
    float x;
    float y;
    uint16_t sign;
    float angle;

public:
    Car(uint16_t &id, float x, float y, uint16_t sign, float angle) : id(id), x(x), y(y), sign(sign), angle(angle) {};
    ~Car() = default;

    //getters
    float getX() const { return x; };
    float getY() const { return y; };
    uint16_t getSign() const { return sign; };
    float getAngle() const { return angle; };
};


#endif //ROCKETLEAGUE_CAR_H
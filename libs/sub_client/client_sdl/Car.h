//
// Created by roby on 27/11/22.
//

#ifndef ROCKETLEAGUE_CAR_H
#define ROCKETLEAGUE_CAR_H


#include <cstdint>
#define HEIGHT 600
#define PXM 37 //  Pixeles por metro
class Car {
private:
    uint16_t& id;
    float x;
    float y;
    uint16_t sign;
    float angle;

public:
    Car(uint16_t &id, float x, float y, uint16_t sign, float angle) : id(id), x(x * PXM), y(HEIGHT - (y * PXM)), sign(sign), angle(angle) {};
    ~Car() = default;

    //getters
    uint16_t getId() const { return id; };
    float getX() const { return x; };
    float getY() const { return y; };
    uint16_t getSign() const { return sign; };
    float getAngle() const { return angle; };
};


#endif //ROCKETLEAGUE_CAR_H
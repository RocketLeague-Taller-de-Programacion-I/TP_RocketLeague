#ifndef ROCKETLEAGUE_CAR_H
#define ROCKETLEAGUE_CAR_H


#include <cstdint>
#define HEIGHT 600 //window height
#define PXM 37 //  Pixeles por metro

#define CAR_W_PX 67
#define CAR_H_PX 30

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
    uint16_t getId() const { return id; };
    float getX() const {
        return (x * PXM) - CAR_W_PX/2;
    };
    float getY() const {
        return HEIGHT - (y * PXM) - CAR_H_PX/2;//mas?
    };
    uint16_t getSign() const { return sign; };
    float getAngle() const { return angle; };
};


#endif //ROCKETLEAGUE_CAR_H
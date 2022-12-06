#ifndef ROCKETLEAGUE_CAR_H
#define ROCKETLEAGUE_CAR_H

#include <cstdint>

enum facingDirection : bool {
    LEFT = true,
    RIGHT = false
};

class Car {
private:
    uint16_t id;
    float x;
    float y;
    float angle;
    int facing;

public:
    Car(uint16_t id, float x, float y, float angle, int facingWhere)
            : id(id), x(x), y(y), angle(angle), facing(facingWhere)  {};
    ~Car() = default;

    //getters
    uint16_t getId() const { return id; };
    float getX() const {
        return x;
    };
    float getY() const {
        return y;//mas?
    };
    float getAngle() const { return angle; };
    bool getFacing() const { return facing; };
};


#endif //ROCKETLEAGUE_CAR_H
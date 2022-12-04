#ifndef ROCKETLEAGUE_GAMETIME_H
#define ROCKETLEAGUE_GAMETIME_H

#include <cstdint>

class GameTime {
private:
    uint16_t time;
public:
    GameTime(uint16_t time) : time(time) {};
    GameTime() { time = 0; };
    ~GameTime() = default;

    uint16_t getTime() const { return time; };
};


#endif //ROCKETLEAGUE_GAMETIME_H

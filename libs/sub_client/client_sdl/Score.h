//
// Created by roby on 27/11/22.
//

#ifndef ROCKETLEAGUE_SCORE_H
#define ROCKETLEAGUE_SCORE_H


#include <cstdint>

class Score {
private:
    uint8_t scoreLocal;
    uint8_t scoreVisitor;
public:
    Score(uint8_t &local, uint8_t &visitor) : scoreLocal(local), scoreVisitor(visitor) {};
    Score() { scoreLocal = 0; scoreVisitor = 0; };
    ~Score() = default;

    uint8_t getLocal() const { return scoreLocal; };
    uint8_t getVisitor() const { return scoreVisitor; };
};


#endif //ROCKETLEAGUE_SCORE_H

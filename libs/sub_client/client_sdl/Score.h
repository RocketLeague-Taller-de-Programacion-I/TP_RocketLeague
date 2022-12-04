#ifndef ROCKETLEAGUE_SCORE_H
#define ROCKETLEAGUE_SCORE_H

#include <cstdint>

class Score {
private:
    uint16_t scoreLocal;
    uint16_t scoreVisitor;
public:
    Score(uint16_t &local, uint16_t &visitor) : scoreLocal(local), scoreVisitor(visitor) {};
    Score() { scoreLocal = 0; scoreVisitor = 0; };
    ~Score() = default;

    uint16_t getLocal() const { return scoreLocal; };
    uint16_t getVisitor() const { return scoreVisitor; };
};


#endif //ROCKETLEAGUE_SCORE_H
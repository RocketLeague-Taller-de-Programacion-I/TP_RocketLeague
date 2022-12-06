#ifndef ROCKETLEAGUE_CLIENTUPDATESTATS_H
#define ROCKETLEAGUE_CLIENTUPDATESTATS_H


#include "ClientUpdate.h"

class ClientUpdateStats : public ClientUpdate {
private:
    std::map<uint8_t,uint8_t> stats;
public:
    explicit ClientUpdateStats(std::map<uint8_t,uint8_t> &stats) : stats(stats) {};
    ~ClientUpdateStats() = default;

    uint8_t getType() const override { return GAME_OVER; };
    std::map<uint8_t,uint8_t> getStats() { return stats; };
};


#endif //ROCKETLEAGUE_CLIENTUPDATESTATS_H

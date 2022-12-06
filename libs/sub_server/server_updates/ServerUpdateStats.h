#ifndef ROCKETLEAGUE_SERVERUPDATESTATS_H
#define ROCKETLEAGUE_SERVERUPDATESTATS_H

#include <functional>

#include "ServerUpdate.h"

class ServerUpdateStats : public ServerUpdate{
private:
    std::vector<int> stats;
public:
    explicit ServerUpdateStats(std::vector<int> &data) : stats(data){};
    ~ServerUpdateStats() override = default;

    uint8_t getType() const override;
    void beSerialized(ServerProtocolo *protocolo, std::function<void(void *, unsigned int)> &sendCallable) override;
    std::vector<int> getStats() const { return stats;};
};


#endif //ROCKETLEAGUE_SERVERUPDATESTATS_H

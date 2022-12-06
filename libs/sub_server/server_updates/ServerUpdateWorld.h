#ifndef ROCKETLEAGUE_SERVERUPDATEWORLD_H
#define ROCKETLEAGUE_SERVERUPDATEWORLD_H

#include <functional>

#include "ServerUpdate.h"

class ServerUpdateWorld : public ServerUpdate{
private:
        std::vector<int> info;
public:
    explicit ServerUpdateWorld(std::vector<int> &data) : info(data){};
    ~ServerUpdateWorld() override = default;

    uint8_t getType() const override;
    void beSerialized(ServerProtocolo *protocolo, std::function<void(void *, unsigned int)> &sendCallable) override;
    std::vector<int> getInfo() const { return info;};
};


#endif //ROCKETLEAGUE_SERVERUPDATEWORLD_H

//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_SERVERLISTACK_H
#define ROCKETLEAGUE_SERVERLISTACK_H

#include <functional>

#include "ServerUpdate.h"

class ServerListACK : public ServerUpdate{
private:
    uint8_t numberOfGames;
public:
    ServerListACK(const uint8_t &id, uint8_t &returnCode, const uint8_t &n) :
                                    ServerUpdate(id, returnCode),
                                    numberOfGames(n){};
    ServerListACK(uint8_t &id, uint8_t &returnCode, const uint8_t &n, std::vector<uint8_t> &returnData) :
                                    ServerUpdate(id, returnCode, returnData),
                                    numberOfGames(n){};

    ~ServerListACK() override = default;

    uint8_t getType() const override;
    void beSerialized(ServerProtocolo *protocolo, std::function<void(void *, unsigned int)> &sendCallable) override;
    uint8_t getNumberOfGames() const { return numberOfGames;};
};


#endif //ROCKETLEAGUE_SERVERLISTACK_H

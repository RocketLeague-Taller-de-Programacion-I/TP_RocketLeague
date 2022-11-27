//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_SERVERLISTACK_H
#define ROCKETLEAGUE_SERVERLISTACK_H

#include "ServerUpdate.h"

class ServerListACK : public ServerUpdate{
private:
    uint8_t numberOfGames;
public:
    ServerListACK(const uint8_t &id, uint8_t &returnCode, const uint8_t &n) :
                                    ServerUpdate(id, returnCode),
                                    numberOfGames(n){};
    ServerListACK(uint8_t &id, uint8_t &returnCode, const uint8_t &n, std::vector<uint8_t> &returnData) :
                                    ServerUpdate(id,returnCode,returnData),
                                    numberOfGames(n){};

    ~ServerListACK() override = default;

    uint8_t getType() const override;
    std::vector<uint8_t> beSerialized() override;
};


#endif //ROCKETLEAGUE_SERVERLISTACK_H

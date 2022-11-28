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
    ServerListACK(const uint8_t &id, uint16_t &returnCode, const uint16_t &n) :
                                    ServerUpdate(id, returnCode),
                                    numberOfGames(n){};
    ServerListACK(uint8_t &id, uint16_t &returnCode, const uint16_t &n, std::vector<uint16_t> &returnData) :
                                    ServerUpdate(reinterpret_cast<uint16_t &>(id), returnCode, returnData),
                                    numberOfGames(n){};

    ~ServerListACK() override = default;

    std::uint16_t getType() const override;
    std::vector<uint16_t> beSerialized() override;
};


#endif //ROCKETLEAGUE_SERVERLISTACK_H

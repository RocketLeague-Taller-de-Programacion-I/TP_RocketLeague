//
// Created by roby on 27/11/22.
//

#ifndef ROCKETLEAGUE_SERVERSTARTEDGAMEACK_H
#define ROCKETLEAGUE_SERVERSTARTEDGAMEACK_H

#include "ServerUpdate.h"

class ServerStartedGameACK : public ServerUpdate{
public:
    ServerStartedGameACK(const uint8_t &id, uint8_t &returnCode) : ServerUpdate(id, returnCode){}
    ~ServerStartedGameACK() override = default;

    uint8_t getType() const override;
    void beSerialized(ServerProtocolo *protocolo, std::function<void(void *, unsigned int)> &sendCallable) override;
};


#endif //ROCKETLEAGUE_SERVERSTARTEDGAMEACK_H

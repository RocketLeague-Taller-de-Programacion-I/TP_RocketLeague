//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_SERVERJOINACK_H
#define ROCKETLEAGUE_SERVERJOINACK_H

#include <functional>

#include "ServerUpdate.h"

class ServerJoinACK : public ServerUpdate{
public:
    ServerJoinACK(const uint8_t &id, uint8_t &returnCode) : ServerUpdate(id, returnCode) {};
    ~ServerJoinACK() override = default;

    uint8_t getType() const override;
    void beSerialized(ServerProtocolo *protocolo, std::function<void(void *, unsigned int)> &sendCallable) override;
};


#endif //ROCKETLEAGUE_SERVERJOINACK_H

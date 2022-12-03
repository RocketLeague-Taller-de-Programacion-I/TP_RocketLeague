//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_SERVERCREATEACK_H
#define ROCKETLEAGUE_SERVERCREATEACK_H

#include "ServerUpdate.h"

class ServerCreateACK : public ServerUpdate{
public:
    ServerCreateACK(const uint8_t &id, uint8_t &returnCode) : ServerUpdate(id, returnCode){};
    ~ServerCreateACK() override = default;

    uint8_t getType() const override;
    void beSerialized(ServerProtocolo *protocolo) override;

};


#endif //ROCKETLEAGUE_SERVERCREATEACK_H

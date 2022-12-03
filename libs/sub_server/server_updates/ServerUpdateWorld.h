//
// Created by roby on 25/11/22.
//

#ifndef ROCKETLEAGUE_SERVERUPDATEWORLD_H
#define ROCKETLEAGUE_SERVERUPDATEWORLD_H

#include "ServerUpdate.h"

class ServerUpdateWorld : public ServerUpdate{
private:
        std::vector<int> info;
public:
    ServerUpdateWorld(uint8_t &id, uint8_t &returnCode, std::vector<uint8_t> &returnData, std::vector<int> &data) :
                                    ServerUpdate(id,returnCode,returnData),
                                    info(data){};
    ~ServerUpdateWorld() override = default;

    uint8_t getType() const override;
    void beSerialized(ServerProtocolo *protocolo) override;
    std::vector<int> getInfo() const { return info;};
};


#endif //ROCKETLEAGUE_SERVERUPDATEWORLD_H

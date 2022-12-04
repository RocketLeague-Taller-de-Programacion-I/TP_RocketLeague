//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_SERVERLISTACK_H
#define ROCKETLEAGUE_SERVERLISTACK_H

#include <functional>

#include "ServerUpdate.h"

class ServerListACK : public ServerUpdate{
private:
    std::vector<uint8_t> listData;
    uint8_t numberOfGames;
public:
    ServerListACK(const uint8_t &id, uint8_t &returnCode, const uint8_t &n) :
                                    ServerUpdate(id, returnCode),
                                    numberOfGames(n){};
    ServerListACK(uint8_t &id, uint8_t &returnCode, const uint8_t &n, std::vector<uint8_t> &returnData) :
                                    ServerUpdate(id, returnCode),
                                    listData(returnData),
                                    numberOfGames(n){};

    ~ServerListACK() override = default;

    uint8_t getType() const override;
    void beSerialized(ServerProtocolo *protocolo, std::function<void(void *, unsigned int)> &sendCallable) override;
    std::vector<uint8_t> getListData() { return listData; };
    uint8_t getNumberOfGames() const { return numberOfGames;};
};


#endif //ROCKETLEAGUE_SERVERLISTACK_H

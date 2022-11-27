//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTLISTACK_H
#define ROCKETLEAGUE_CLIENTLISTACK_H

#include "ClientUpdate.h"

class ClientListACK : public ClientUpdate {
private:
    std::map<std::string,std::string> listData;
public:
    ClientListACK(uint8_t &id, uint8_t &returnCode, std::map<std::string, std::string> &listMap);
    ClientListACK(uint8_t &id, uint8_t &returnCode);
    ~ClientListACK() = default;

    std::map<std::string, std::string> getList();
};


#endif //ROCKETLEAGUE_CLIENTLISTACK_H

//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTLISTACK_H
#define ROCKETLEAGUE_CLIENTLISTACK_H

#include "ClientUpdate.h"

class ClientListACK : public ClientUpdate {
public:
    ClientListACK(uint8_t &id, std::string &list);
    ~ClientListACK() = default;

    std::vector<std::string> getList();
};


#endif //ROCKETLEAGUE_CLIENTLISTACK_H

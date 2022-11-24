//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTCREATEACK_H
#define ROCKETLEAGUE_CLIENTCREATEACK_H

#include "ClientUpdate.h"

class ClientCreateACK : public ClientUpdate{
private:
    std::string returnCode;
public:
    ClientCreateACK(uint8_t &id, std::string &returnCode);
    ~ClientCreateACK() = default;
};


#endif //ROCKETLEAGUE_CLIENTCREATEACK_H

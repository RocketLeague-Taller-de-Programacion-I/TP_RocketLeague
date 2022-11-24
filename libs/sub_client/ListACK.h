//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_LISTACK_H
#define ROCKETLEAGUE_LISTACK_H

#include "GameUpdate.h"

class ListACK : public GameUpdate {
public:
    ListACK(uint8_t &id, std::string &list);
    ~ListACK() = default;

    std::vector<std::string> getList();
};


#endif //ROCKETLEAGUE_LISTACK_H

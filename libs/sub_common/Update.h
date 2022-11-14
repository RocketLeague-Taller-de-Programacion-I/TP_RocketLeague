//
// Created by lucaswaisten on 12/11/22.
//

#ifndef ROCKETLEAGUE_UPDATE_H
#define ROCKETLEAGUE_UPDATE_H


#include "Information.h"

class Update : public Information {
public:
    explicit Update(const std::uint8_t &type, std::vector<uint8_t>& data);

};


#endif //ROCKETLEAGUE_UPDATE_H

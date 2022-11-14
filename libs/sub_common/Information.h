//
// Created by lucaswaisten on 13/11/22.
//

#ifndef ROCKETLEAGUE_INFORMATION_H
#define ROCKETLEAGUE_INFORMATION_H


#include <cstdint>
#include <vector>

class Information {
protected:
    Information(uint8_t aType, std::vector<uint8_t> aData);
    std::uint8_t type;
    std::vector<uint8_t> data;
};


#endif //ROCKETLEAGUE_INFORMATION_H
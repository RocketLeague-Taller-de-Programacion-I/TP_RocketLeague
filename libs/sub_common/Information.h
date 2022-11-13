//
// Created by lucaswaisten on 13/11/22.
//

#ifndef ROCKETLEAGUE_INFORMATION_H
#define ROCKETLEAGUE_INFORMATION_H


#include <cstdint>
#include <vector>

class Information {
protected:
    Information(uint8_t aType, std::vector<char> aData);
    std::uint8_t type;
    std::vector<char> data;
};


#endif //ROCKETLEAGUE_INFORMATION_H

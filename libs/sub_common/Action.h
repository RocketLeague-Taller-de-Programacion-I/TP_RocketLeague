//
// Created by roby on 12/11/22.
//

#ifndef ROCKETLEAGUE_ACTION_H
#define ROCKETLEAGUE_ACTION_H

#include <cstdint>
#include <string>
#include <vector>

class Action {
public:
    explicit Action(const std::uint8_t &type, std::vector<char>& data);
    explicit Action(const std::uint8_t &type, std::string & data);

    std::uint8_t type;
    std::vector<char> data;

    std::uint8_t getType() const;
};


#endif //ROCKETLEAGUE_ACTION_H

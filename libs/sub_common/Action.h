//
// Created by roby on 12/11/22.
//

#ifndef ROCKETLEAGUE_ACTION_H
#define ROCKETLEAGUE_ACTION_H


#include <cstdint>

enum actionType {
    CREATE_ROOM,
    JOIN_ROOM,
    LIST_ROOMS,
    MOVE
};

class Action {
public:
    explicit Action(const std::uint8_t &type, std::vector<char>& data);

public:
    std::uint8_t type;
    std::vector<char> data;

    std::uint8_t getType() const;
};


#endif //ROCKETLEAGUE_ACTION_H

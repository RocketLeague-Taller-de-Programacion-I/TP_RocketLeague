//
// Created by lucaswaisten on 12/11/22.
//

#ifndef ROCKETLEAGUE_ACTION_H
#define ROCKETLEAGUE_ACTION_H

#include <cstdint>
#include <string>
#include <vector>
#include "sub_server/gameManager.h"

enum actionType {
    CREATE_ROOM,
    JOIN_ROOM,
    LIST_ROOMS,
    MOVE
};

class Action {
public:
    explicit Action(const std::uint8_t &type, std::vector<char>& data);
    explicit Action(const std::uint8_t &type, std::string & data);
    std::uint8_t getType() const;


    std::string excecute(GameManager &manager);

private:
    std::uint8_t type;
    std::vector<char> data;

};


#endif //ROCKETLEAGUE_ACTION_H

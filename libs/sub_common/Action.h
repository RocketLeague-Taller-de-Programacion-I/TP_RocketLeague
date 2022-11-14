//
// Created by lucaswaisten on 12/11/22.
//

#ifndef ROCKETLEAGUE_ACTION_H
#define ROCKETLEAGUE_ACTION_H

#include <cstdint>
#include <string>
#include <vector>
#include "sub_server/gameManager.h"
#include "Information.h"

enum actionType {
    CREATE_ROOM,
    JOIN_ROOM,
    LIST_ROOMS,
    MOVE
};

class Action : public Information{
public:
    explicit Action(const std::uint8_t &type, std::vector<uint8_t>& data);
    explicit Action(const std::uint8_t &type, std::string & data);
    std::uint8_t getType() const;
    std::vector<uint8_t> getData() const;
    std::string excecute(GameManager &manager);

};


#endif //ROCKETLEAGUE_ACTION_H
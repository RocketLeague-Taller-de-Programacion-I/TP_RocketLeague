//
// Created by lucaswaisten on 12/11/22.
//

#ifndef ROCKETLEAGUE_ACTION_H
#define ROCKETLEAGUE_ACTION_H

#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "Information.h"
#include "sub_server/ClientManager.h"

enum actionType {
    CREATE_ROOM,
    JOIN_ROOM,
    LIST_ROOMS,
    MOVE
};

class Action : public Information{
public:
    explicit Action(const std::uint8_t &type, std::vector<char>& data);
    explicit Action(const std::uint8_t &type, std::string & data);
    std::uint8_t getType() const;
    void excecute(GameManager &manager, ClientManager *i);

};


#endif //ROCKETLEAGUE_ACTION_H

//
// Created by lucaswaisten on 04/11/22.
//
#pragma once

#ifndef ROCKETLEAGUE_SERVERPROTOCOLO_H
#define ROCKETLEAGUE_SERVERPROTOCOLO_H

#include <cstdint>
#include <SDL2/SDL_keycode.h>
#include <string>
#include <unordered_map>
#include <memory>

#include "server_updates/ServerUpdate.h"

#include "sub_server/server_actions/ServerCreateRoom.h"
#include "sub_server/server_actions/ServerJoinRoom.h"
#include "sub_server/server_actions/ServerListRooms.h"
#include "sub_server/server_actions/ServerActionMove.h"

class Protocolo {
public:
//    std::vector<uint8_t> serializeAction(ServerAction *action);

    ServerAction *deserializeData(const uint8_t &id, const uint8_t &type,
                                  const std::function<void(std::vector<uint8_t> &, uint8_t &)> &receiveBytes);

    static std::vector<uint8_t> serializeCreateAction(const std::vector<uint8_t>& data);
    static std::vector<uint8_t> serializeUpdateAction(const std::vector<uint8_t>& data);
    static std::vector<uint8_t> serializeUpdateWorld(std::vector<int>& data);

    static ServerAction *parseCreateAction(const uint8_t &id, const std::function<void(std::vector<uint8_t> &,
                                                                                       uint8_t &)> &receiveBytes);
    static ServerAction *parseJoinAction(const uint8_t &id, const std::function<void(std::vector<uint8_t> &,
                                                                                     uint8_t &)> &receiveBytes);
    static ServerAction *parseListAction(const uint8_t &id);

    ServerAction *
    parseMoveAction(const uint8_t &id, const std::function<void(std::vector<uint8_t> &, uint8_t &)> &receiveBytes);
};


#endif //ROCKETLEAGUE_SERVERPROTOCOLO_H

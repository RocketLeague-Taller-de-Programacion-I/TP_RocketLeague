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

#include "server_updates/ServerCreateACK.h"
#include "server_updates/ServerJoinACK.h"
#include "server_updates/ServerListACK.h"
#include "server_updates/ServerUpdateWorld.h"

#include "sub_server/server_actions/ServerCreateRoom.h"
#include "sub_server/server_actions/ServerJoinRoom.h"
#include "sub_server/server_actions/ServerListRooms.h"


enum action {
    NOP,
    JUMP,
    RIGHT,
    LEFT,
    UP,
    DOWN,
    TURBO
} ;

typedef uint8_t command_t;

class ServerProtocolo {
private:
    const std::unordered_map<uint32_t , command_t> mapCommand = {
            {SDLK_ESCAPE, NOP},
            {SDLK_SPACE, JUMP},
            {SDLK_RIGHT, RIGHT},
            {SDLK_LEFT, LEFT},
            {SDLK_UP, UP},
            {SDLK_DOWN, DOWN},
            {SDLK_SPACE, TURBO}
    };
    const std::function<void(void*, unsigned int)> &sendBytes;
public:
    command_t getMapCommand(uint32_t action);
    ServerProtocolo(const std::function<void(void *, unsigned int)> &sendBytesCallable) : sendBytes(sendBytesCallable) {};

    static std::shared_ptr<ServerAction> deserializeData(const uint8_t &id, const uint8_t &type,
                                                         const std::function<void(std::vector<uint8_t> &, uint8_t &)> &receiveBytes);
    void serializeUpdate(std::shared_ptr<ServerUpdate> update);
    void serializeCreateACK(ServerCreateACK *update);
    void serializeJoinACK(ServerJoinACK *update);
    void serializeServerListACK(ServerListACK *update);
    void serializeWorldUpdate(ServerUpdateWorld *update);

    static std::shared_ptr<ServerAction> parseCreateAction(const uint8_t &id, const std::function<void(std::vector<uint8_t> &,
                                                                                                       uint8_t &)> &receiveBytes);

    static std::shared_ptr<ServerAction> parseJoinAction(const uint8_t &id, const std::function<void(std::vector<uint8_t> &,
                                                                                                     uint8_t &)> &receiveBytes);

    static std::shared_ptr<ServerAction> parseListAction(const uint8_t &id);

    static std::unique_ptr<ServerAction> parseUpdateAction();
};


#endif //ROCKETLEAGUE_SERVERPROTOCOLO_H

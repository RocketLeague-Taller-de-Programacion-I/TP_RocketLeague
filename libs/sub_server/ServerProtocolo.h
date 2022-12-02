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
#include <iostream>

#include "server_updates/ServerCreateACK.h"
#include "server_updates/ServerJoinACK.h"
#include "server_updates/ServerListACK.h"
#include "server_updates/ServerUpdateWorld.h"

#include "sub_server/server_actions/ServerCreateRoom.h"
#include "sub_server/server_actions/ServerJoinRoom.h"
#include "sub_server/server_actions/ServerListRooms.h"
#include "sub_server/server_actions/ServerActionMove.h"

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
public:
    command_t getMapCommand(uint32_t action);
    ServerProtocolo() = default;

    static std::shared_ptr<ServerAction> deserializeData(const uint8_t &id, const uint8_t &type,
                                                         const std::function<void(void *, int)> &receiveBytes);
    static std::shared_ptr<ServerAction>
    parseUpdateAction(const std::function<void(void *, int)> &receiveBytes);

    static std::shared_ptr<ServerAction>
    deserializeDataOnCommand(uint8_t &actionType,
                             uint8_t &id,
                             GameManager &gameManager,
                             std::function<void(void *, int)> &receiveBytes,
                             std::function<void(void *, unsigned int)> &sendBytes,
                             std::function<void(ProtectedQueue<std::shared_ptr<ServerAction>> *,
                                                BlockingQueue<std::shared_ptr<ServerUpdate>> *)> &startThreadsCallable);

    static std::shared_ptr<ServerAction>
    parseCreateAction(uint8_t &id, const std::function<void(void *, int)>& receiveBytes,
                      GameManager &gameManager);
    static std::shared_ptr<ServerAction>
    parseJoinAction(const uint8_t &id, const std::function<void(void *, int)> &receiveBytes,
                    GameManager &gameManager);
    static std::shared_ptr<ServerAction>
    parseListAction(const uint8_t &id,
                    GameManager &gameManager);

    void serializeUpdate(std::shared_ptr<ServerUpdate> update,
                         std::function<void(void *, unsigned int)> &sendCallable);
    static void serializeCreateACK(ServerCreateACK *update, std::function<void(void *, unsigned int)> &sendBytes);
    void serializeJoinACK(ServerJoinACK *update, std::function<void(void *, unsigned int)> &sendBytes);
    void serializeServerListACK(ServerListACK *update, std::function<void(void *, unsigned int)> &sendBytes);
    void serializeWorldUpdate(ServerUpdateWorld *update, std::function<void(void *, unsigned int)> &sendBytes);
};


#endif //ROCKETLEAGUE_SERVERPROTOCOLO_H

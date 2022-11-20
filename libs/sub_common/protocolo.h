//
// Created by lucaswaisten on 04/11/22.
//
#pragma once

#ifndef ROCKETLEAGUE_PROTOCOLO_H
#define ROCKETLEAGUE_PROTOCOLO_H

#include <cstdint>
#include <SDL2/SDL_keycode.h>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include "sub_common/sub_action/Action.h"

typedef uint8_t command_t;

class Protocolo {
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

    std::vector<uint8_t> serializeAction(Action *action);

    void parseCreateRoomData(Action *action, std::vector<uint8_t> &result) const;

    std::unique_ptr<Action> deserializeData(const std::vector<uint8_t>& data);

    static std::unique_ptr<Action> parseCreateAction(const std::vector<uint8_t> &data);

    static std::unique_ptr<Action> parseJoinAction(const std::vector<uint8_t> &data);

    static std::unique_ptr<Action> parseListAction(const std::vector<uint8_t> &data);
};


#endif //ROCKETLEAGUE_PROTOCOLO_H

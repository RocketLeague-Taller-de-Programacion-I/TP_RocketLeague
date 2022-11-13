//
// Created by lucaswaisten on 04/11/22.
//

#ifndef ROCKETLEAGUE_PROTOCOLO_H
#define ROCKETLEAGUE_PROTOCOLO_H


#include <cstdint>
#include <SDL2/SDL_keycode.h>
#include <string>
#include <unordered_map>

enum action{
    NOP_C,
    JUMP_C,
    RIGHT_C,
    LEFT_C,
    UP_C,
    DOWN_C,
    TURBO_C,
    CREATE_C,
    LIST_C,
    JOIN_C
};

typedef uint8_t command_t;

class Protocolo {
private:
    const std::unordered_map<uint32_t , command_t> mapCommand = {
            {SDLK_ESCAPE, NOP_C},
            {SDLK_SPACE, JUMP_C},
            {SDLK_RIGHT, RIGHT_C},
            {SDLK_LEFT, LEFT_C},
            {SDLK_UP, UP_C},
            {SDLK_DOWN, DOWN_C},
            {SDLK_KP_C, TURBO_C},
            {SDLK_0, CREATE_C},
            {SDLK_1, LIST_C},
            {SDLK_2, JOIN_C}
    };
public:
    command_t getMapCommand(uint32_t action);
};


#endif //ROCKETLEAGUE_PROTOCOLO_H

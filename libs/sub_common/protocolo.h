//
// Created by lucaswaisten on 04/11/22.
//

#ifndef ROCKETLEAGUE_PROTOCOLO_H
#define ROCKETLEAGUE_PROTOCOLO_H


#include <cstdint>
#include <SDL2/SDL_keycode.h>
#include <string>
#include <unordered_map>
#include "Action.h"

enum actionType {
    CREATE_ROOM,
    JOIN_ROOM,
    LIST_ROOMS,
    MOVE
};

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

    std::vector<uint8_t> serializeAction(Action action);

    void parseCreateRoomData(Action &action, std::vector<uint8_t> &result) const;

    Action deserializarData(const std::vector<uint8_t>& data);

    ActionCreate parseCreateAction(const std::vector<uint8_t> &data);

    ActionJoin parseJoinAction(const std::vector<uint8_t> &data);

    ActionList parseListAction(const std::vector<uint8_t> &data);
};


#endif //ROCKETLEAGUE_PROTOCOLO_H

//
// Created by lucaswaisten on 01/11/22.
//

#ifndef ROCKETLEAGUE_PROTOCOLO_H
#define ROCKETLEAGUE_PROTOCOLO_H


#include <cstdint>
#include <string>
#include <unordered_map>

enum action{
    NOP,
    JUMP,
    RIGHT,
    LEFT,
    UP,
    DOWN,
    TURBO
};
enum menu{
    CREATE,
    LIST,
    JOIN
};
typedef uint8_t command_t;

class Protocolo {
private:
    const std::unordered_map<std::string, command_t> mapCommand = {
            {"nop", NOP},
            {"jump", JUMP},
            {"right", RIGHT},
            {"left", LEFT},
            {"up", UP},
            {"down", DOWN},
            {"turbo", TURBO},
    };
    const std::unordered_map<std::string, command_t> mapMenuCommand = {
            {"create", CREATE},
            {"list", LIST},
            {"join", JOIN}
    };
public:
    uint8_t serializeAction(const std::string &action);

    command_t serializeMenuAction(const std::string &menuAction);
};


#endif //ROCKETLEAGUE_PROTOCOLO_H

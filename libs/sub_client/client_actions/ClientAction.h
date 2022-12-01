//
// Created by roby on 22/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTACTION_H
#define ROCKETLEAGUE_CLIENTACTION_H


#include <utility>
#include <cstdint>
#include <string>
#include <vector>
#include <functional>

enum action_type {
    CREATE = 1,
    JOIN,
    LIST,
    MOVE
};

enum direction {
    RIGHT_D = 0,
    LEFT_D = 1,
    JUMP_D = 2,
    DOWN_D = 3,
    TURBO_D = 4
} ;
enum state : bool {
    ON = true,
    OFF = false
};

class ClientAction {
protected:
    uint8_t type;
    std::vector<uint8_t> data;
public:
    ClientAction() = default;

    virtual ~ClientAction() = default;

    virtual std::uint8_t getType() const = 0;
    virtual std::vector<uint8_t> beSerialized() = 0;
};



#endif //ROCKETLEAGUE_CLIENTACTION_H

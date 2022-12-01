//
// Created by roby on 22/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTACTION_H
#define ROCKETLEAGUE_CLIENTACTION_H

class ClientProtocol;
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
    RIGHT_D,
    LEFT_D,
    JUMP_D,
    DOWN_D,
    TURBO_D
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
    virtual void beSerialized(ClientProtocol *protocolo) = 0;
};



#endif //ROCKETLEAGUE_CLIENTACTION_H

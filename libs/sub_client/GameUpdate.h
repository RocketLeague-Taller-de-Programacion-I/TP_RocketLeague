//
// Created by roby on 22/11/22.
//

#ifndef ROCKETLEAGUE_GAMEUPDATE_H
#define ROCKETLEAGUE_GAMEUPDATE_H

#include <vector>
#include <string>

enum updateType {
    CREATE_ACK = 1,
    JOIN_ACK = 2,
    LIST_INFO = 3,
    WORLD = 4
};

class GameUpdate {
protected:
    uint8_t id;
    std::string data;
public:
    GameUpdate() = default;
    GameUpdate(uint8_t& id, std::string &returnCode);

    virtual ~GameUpdate() = default;

    virtual uint8_t getId() const { return id;};
    virtual std::string getData() const { return data;};
};


#endif //ROCKETLEAGUE_GAMEUPDATE_H

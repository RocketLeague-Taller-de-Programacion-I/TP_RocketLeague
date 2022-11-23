//
// Created by roby on 22/11/22.
//

#ifndef ROCKETLEAGUE_GAMEUPDATE_H
#define ROCKETLEAGUE_GAMEUPDATE_H

#include <vector>
#include <string>

enum updateType {
    CREATE_ACK = 1,
    JOIN_ACK,
    LIST_INFO,
    WORLD
};

enum returnCode {
    OK = 1,
    NAME_TAKEN,
    GAME_FULL,
    GAME_NOT_FOUND
};

class GameUpdate {
private:
    std::vector<uint8_t> data;
public:
    GameUpdate(std::vector<uint8_t>& data);
    ~GameUpdate() = default;

    std::string getList();
//    std::string getReturnCode();
    uint8_t getId();
};


#endif //ROCKETLEAGUE_GAMEUPDATE_H

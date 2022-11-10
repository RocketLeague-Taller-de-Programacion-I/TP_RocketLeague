//
// Created by lucaswaisten on 04/11/22.
//

#ifndef ROCKETLEAGUE_GAMEMANAGER_H
#define ROCKETLEAGUE_GAMEMANAGER_H


#include <map>
#include <mutex>
#include "game.h"

class GameManager {
    std::mutex mutex;
    std::map<std::string ,Game&> games;
public:
    uint8_t createGame(uint8_t aCantPlayers,
                       const std::string& aGameName);

    uint8_t joinGame(const std::string &aGameName);

    std::string listGames();

    void cleanGames();
};


#endif //ROCKETLEAGUE_GAMEMANAGER_H

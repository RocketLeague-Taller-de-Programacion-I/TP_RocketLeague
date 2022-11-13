//
// Created by lucaswaisten on 04/11/22.
//

#ifndef ROCKETLEAGUE_GAMEMANAGER_H
#define ROCKETLEAGUE_GAMEMANAGER_H


#include <map>
#include <mutex>
#include <vector>
#include "game.h"
#include "sub_common/Update.h"

class GameManager {
    std::mutex mutex;
    std::map<std::string ,Game&> games;
public:
    std::string createGame(std::vector<char> &data);

    std::string joinGame(std::vector<char> &data);

    std::string listGames();

    void cleanGames();

    std::string move(std::vector<char> data);

    void sendUpdate(Update &update);
};


#endif //ROCKETLEAGUE_GAMEMANAGER_H

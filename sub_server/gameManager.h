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
    std::map<std::string ,Game> partidas;
};


#endif //ROCKETLEAGUE_GAMEMANAGER_H

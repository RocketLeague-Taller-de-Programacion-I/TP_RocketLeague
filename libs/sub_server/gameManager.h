//
// Created by lucaswaisten on 04/11/22.
//
#pragma once

#ifndef ROCKETLEAGUE_GAMEMANAGER_H
#define ROCKETLEAGUE_GAMEMANAGER_H

#include <map>
#include <mutex>
#include <vector>
#include "game.h"
#include "sub_common/Action.h"

class GameManager {
    std::mutex mutex;
    std::map<std::string ,Game*> games;
public:
   void listGames();
   void cleanGames();

    void createGame(uint8_t &idCreator, uint8_t &capacityGame, const std::string& nameGame,
                    std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> startClientThreads);

    void joinGame(uint8_t &idCreator, const std::string& nameGame, std::function<void(BlockingQueue<Action *> *,
                                                                                      BlockingQueue<Action *> *)> startClientThreads);
};

#endif // ROCKETLEAGUE_GAMEMANAGER_H
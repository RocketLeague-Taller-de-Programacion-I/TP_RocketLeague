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

class GameManager {
    std::mutex mutex;
    std::map<std::string ,Game&> games;
public:
   //std::string joinGame(uint8_t id, ClientManager *pManager, const std::string& name);
   void listGames();
   void cleanGames();

    void createGame(uint8_t idCreator, uint8_t capacityGame, const std::string& nameGame,
                    std::function<void(BlockingQueue<Action> *)> setQueue);

    void joinGame(uint8_t idCreator, const std::string& nameGame, std::function<void(BlockingQueue<Action> *)> setQueue);
};

#endif // ROCKETLEAGUE_GAMEMANAGER_H
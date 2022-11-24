//
// Created by lucaswaisten on 04/11/22.
//
#pragma once
#ifndef ROCKETLEAGUE_GAMEMANAGER_H
#define ROCKETLEAGUE_GAMEMANAGER_H
class Action;
#include <map>
#include <mutex>
#include <vector>
#include "game.h"
#include <functional>

class GameManager {
    std::mutex mutex;
    std::map<std::string, Game*> games;
public:
   //std::string joinGame(uint8_t id, ClientManager *pManager, const std::string& name);
   std::string listGames(uint8_t &id);
   void cleanGames();

    bool createGame(uint8_t idCreator, uint8_t capacityGame, const std::string& nameGame,
                    const std::function<BlockingQueue<Action *> *(ProtectedQueue<Action *> *)> &setQueue);

    bool joinGame(uint8_t idCreator, const std::string& nameGame, std::function<BlockingQueue<Action *> *(
            ProtectedQueue<Action *> *)> setQueue);

};

#endif // ROCKETLEAGUE_GAMEMANAGER_H
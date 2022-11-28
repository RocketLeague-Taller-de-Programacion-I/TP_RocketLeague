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
#include <functional>


class GameManager {
    std::mutex mutex;
    std::map<std::string, Game*> games;
public:
   uint8_t listGames(uint8_t &id, std::vector<uint8_t> &listData);
    bool createGame(uint8_t idCreator, uint8_t capacityGame,
                    const std::string& nameGame,std::function<BlockingQueue<std::shared_ptr<ServerUpdate>> *(
            ProtectedQueue<ServerAction *> *)> setQueue);
    bool joinGame(uint8_t idCreator, const std::string& nameGame, std::function<BlockingQueue<std::shared_ptr<ServerUpdate>> *(
            ProtectedQueue<ServerAction *> *)> setQueue);

    void cleanGames();
};

#endif // ROCKETLEAGUE_GAMEMANAGER_H
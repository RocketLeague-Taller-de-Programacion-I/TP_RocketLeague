//
// Created by lucaswaisten on 04/11/22.
//
#pragma once
#ifndef ROCKETLEAGUE_GAMEMANAGER_H
#define ROCKETLEAGUE_GAMEMANAGER_H

#include <iostream>
#include <map>
#include <mutex>
#include <vector>
#include <functional>
#include "game.h"

class GameManager {
    std::mutex mutex;
    std::map<std::string, Game*> games; //TODO: guardar en stack
public:
   uint8_t listGames(uint8_t &id, std::vector<uint8_t> &listData);
    bool createGame(uint8_t idCreator, uint8_t capacityGame,
                    const std::string& nameGame, std::function<void(ProtectedQueue<std::shared_ptr<ServerAction>> *,
                                                                    BlockingQueue<std::shared_ptr<ServerUpdate>> *)> &startThreadsCallable);
    bool joinGame(uint8_t idCreator, const std::string& nameGame, std::function<void(
            ProtectedQueue<std::shared_ptr<ServerAction>> *,
            BlockingQueue<std::shared_ptr<ServerUpdate>> *)> &startThreadsCallable);

    void cleanGames();

    void deletePlayer(uint8_t idPlayer);
};

#endif // ROCKETLEAGUE_GAMEMANAGER_H
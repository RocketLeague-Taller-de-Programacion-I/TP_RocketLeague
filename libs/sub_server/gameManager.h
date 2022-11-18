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
#include "ClientManager.h"
#include "sub_common/ActionJoin.h"
#include "sub_common/ActionCreate.h"
#include "sub_common/ActionList.h"

class ClientManager;

class GameManager {
    std::mutex mutex;
    std::map<std::string ,Game&> games;
public:
   void createGame(unsigned char id, unsigned char capacity, ClientManager *pClientManager, const std::string& name);
   std::string joinGame(uint8_t id, ClientManager *pManager, const std::string& name);
   void listGames();
   void cleanGames();

};

#endif // ROCKETLEAGUE_GAMEMANAGER_H
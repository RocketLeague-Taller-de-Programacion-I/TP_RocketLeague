//
// Created by lucaswaisten on 04/11/22.
//

#include <iostream>
#include "gameManager.h"
#include "ActionCreate.h"
#include "ActionList.h"
#include "ActionJoin.h"
#include "ActionUpdate.h"

void GameManager::cleanGames() {
    for (auto & game: games) {
        delete &game.second;
    }
}

std::string GameManager::listGames(uint8_t &id, std::string &name) {
    std::unique_lock<std::mutex> lock(this->mutex);
    std::string mensaje("");

    for (auto & partida : this->games) {
        mensaje.append(partida.second->information());
        mensaje.append(",");
    }
    return mensaje;
}

void GameManager::createGame(uint8_t idCreator, uint8_t capacityGame, const std::string& nameGame,
                             const std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)>& startClientThreads) {
    std::unique_lock<std::mutex> lock(this->mutex);

    auto *queueGame = new BlockingQueue<Action*>;

    if (games.find(nameGame) == games.end()) {
        games[nameGame] = new Game(capacityGame,nameGame,queueGame);
    } else {
        throw std::runtime_error("Game already exists");
    }

    auto *queueSender = new BlockingQueue<Action*>;
    games[nameGame]->joinPlayer(idCreator,queueSender);
    startClientThreads(queueGame, queueSender);
    // only start sending updates after game is full
}

void GameManager::joinGame(uint8_t idCreator, const std::string& nameGame, std::function<void(BlockingQueue<Action *> *,BlockingQueue<Action *> *)> startClientThreads) {

    std::unique_lock<std::mutex> lock(this->mutex);
    if (this->games.find(nameGame) == this->games.end()) {
        throw std::runtime_error("Room does not exist");
    } else if (this->games[nameGame]->isFull()) {
        throw std::runtime_error("Room is full");
    } else {
        auto *queueSender = new BlockingQueue<Action*>;
        games[nameGame]->joinPlayer(idCreator,queueSender);
        startClientThreads(games[nameGame]->getQueue(), queueSender);
    }
}

// create new function for gameManager that uses doble dispatch to execute an action
std::string GameManager::executeAction(uint8_t actionType, uint8_t &idCreator, uint8_t &capacity, std::string &name,
                                const std::function<void(BlockingQueue<Action *> *,
                                                         BlockingQueue<Action *> *)> &startClientThreads) {

    std::string mensaje("");
    switch (actionType) {
        case CREATE_ROOM:
            createGame(idCreator,capacity, name,startClientThreads);
            break;
        case JOIN_ROOM:
            joinGame(idCreator,name,startClientThreads);
            break;
        case LIST_ROOMS:
            mensaje = listGames(idCreator,name);
            break;
    }
    return mensaje;
}




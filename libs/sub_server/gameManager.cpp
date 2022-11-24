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

std::string GameManager::listGames(uint8_t &id) {
    std::unique_lock<std::mutex> lock(this->mutex);
    std::string message("");
    if (this->games.empty()) { return message; }

    for (auto & partida : this->games) {
        message.append(partida.second->information());
        message.append(",");
    }
    return message;
}

void GameManager::createGame(uint8_t idCreator, uint8_t capacityGame, const std::string& nameGame,
                             const std::function<BlockingQueue<Action *> *(ProtectedQueue<Action *> *)> &setQueue) {

    std::unique_lock<std::mutex> lock(this->mutex);

    if (games.find(nameGame) == games.end()) {
        auto *queueGame = new ProtectedQueue<Action *>;
        games[nameGame] = new Game(capacityGame,nameGame,queueGame);
    } else {
        throw std::runtime_error("Game already exists");
    }
    auto *queueSender = setQueue(games[nameGame]->getQueue());
    games[nameGame]->joinPlayer(idCreator,queueSender);
}

void GameManager::joinGame(uint8_t idCreator, const std::string& nameGame, std::function<BlockingQueue<Action *> *(
        ProtectedQueue<Action *> *)> setQueue) {

    std::unique_lock<std::mutex> lock(this->mutex);
    if (this->games.find(nameGame) == this->games.end()) {
        // TODO: return update with ERROR message
        throw std::runtime_error("Room does not exist");
    } else if (this->games[nameGame]->isFull()) {
        // TODO: return update with ERROR message
        throw std::runtime_error("Room is full");
    } else {
        auto *queueSender = setQueue(games[nameGame]->getQueue());
        games[nameGame]->joinPlayer(idCreator,queueSender);
    }
}




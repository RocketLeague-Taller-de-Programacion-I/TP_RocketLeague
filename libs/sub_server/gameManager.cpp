//
// Created by lucaswaisten on 04/11/22.
//

#include <iostream>
#include "gameManager.h"
#include "sub_common/ActionCreate.h"
#include "sub_common/ActionList.h"
#include "sub_common/ActionJoin.h"
#include "sub_common/ActionUpdate.h"

void GameManager::cleanGames() {
    for (auto & game: games) {
        delete &game.second;
    }
}

void GameManager::listGames(uint8_t &id, std::string &name) {
    std::unique_lock<std::mutex> lock(this->mutex);
    std::string mensaje("");

    for (auto & partida : this->games) {
        mensaje.append(partida.second->information());
        mensaje.append(",");
    }
    /*
     * send the Update with the data
     */
    games[name]->broadcastUpdate(new ActionUpdate(id, mensaje), id);
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
    // broadcast new update with right id to the client
    std::string mensaje = "OK";
    ActionUpdate *update = new ActionUpdate(idCreator, mensaje); //creacion de partida, devuelve el id
    games[nameGame]->broadcastUpdate(update, idCreator);
}

void GameManager::joinGame(uint8_t idCreator, const std::string& nameGame, std::function<void(BlockingQueue<Action *> *,BlockingQueue<Action *> *)> startClientThreads) {

    std::unique_lock<std::mutex> lock(this->mutex);

    auto iter = games.find(nameGame);

    if (iter->first == nameGame) {
        auto *queueSender = new BlockingQueue<Action*>;
        iter->second->joinPlayer(idCreator,queueSender);
        startClientThreads(iter->second->getQueue(), queueSender);
        if(iter->second->isFull()) {

            iter->second->start();
        }
    }
}

// create new function for gameManager that uses doble dispatch to execute an action
void GameManager::executeAction(uint8_t actionType, uint8_t &idCreator, uint8_t &capacity, std::string &name,
                                const std::function<void(BlockingQueue<Action *> *,
                                                         BlockingQueue<Action *> *)> &startClientThreads) {

    switch (actionType) {
        case CREATE_ROOM:
            createGame(idCreator,capacity, name,startClientThreads);
            break;
        case JOIN_ROOM:
            joinGame(idCreator,name,startClientThreads);
            break;
        case LIST_ROOMS:
            listGames(idCreator,name);
            break;
    }
}




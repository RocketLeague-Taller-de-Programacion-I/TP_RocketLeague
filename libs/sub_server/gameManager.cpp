//
// Created by lucaswaisten on 04/11/22.
//

#include <iostream>
#include "gameManager.h"


std::string GameManager::listGames() {
    std::unique_lock<std::mutex> lock(this->mutex);
    std::string mensaje;
    for (auto & partida : games) {
        mensaje.append(partida.second.information());
        mensaje.append(",");
    }
    return mensaje;
}

void GameManager::createGame(uint8_t idCreator, uint8_t capacityGame, const std::string& nameGame,
                             const std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)>& startClientThreads) {
    std::unique_lock<std::mutex> lock(this->mutex);
    auto *queueGame = new BlockingQueue<Action*>;
    auto *pGame =  new Game(capacityGame,
                            nameGame,
                            queueGame);


    std::pair<std::map<std::string,Game&>::iterator,bool> ret;
    auto iter = games.insert(std::pair<std::string,Game&>(nameGame, (Game &) pGame));

    if (iter.second) {
        auto *queueSender = new BlockingQueue<Action*>;
        pGame->joinPlayer(idCreator,queueSender);
        startClientThreads(queueGame, queueSender);
    }
}


void GameManager::joinGame(uint8_t idCreator, const std::string& nameGame, std::function<void(BlockingQueue<Action *> *,BlockingQueue<Action *> *)> startClientThreads) {

    std::unique_lock<std::mutex> lock(this->mutex);
    auto iter = games.find(nameGame);
    if (iter->first == nameGame) {
        auto *queueSender = new BlockingQueue<Action*>;
        iter->second.joinPlayer(idCreator,queueSender);
        startClientThreads(iter->second.getQueue(), queueSender);
        if(iter->second.isFull()) {
            iter->second.start();
        }
    }


}
void GameManager::cleanGames() {
    for (auto & game: games) {
        delete &game.second;
    }
}

/* create new function for gameManager that uses doble dispatch to execute an action
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
}*/




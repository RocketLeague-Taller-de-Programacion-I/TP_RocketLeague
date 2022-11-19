//
// Created by lucaswaisten on 04/11/22.
//

#include <iostream>
#include "gameManager.h"
#include "sub_common/Update.h"

void GameManager::cleanGames() {
    for (auto & game: games) {
        delete &game.second;
    }
}

void GameManager::listGames() {
    std::unique_lock<std::mutex> lock(this->mutex);
    std::string mensaje("OK");

    for (auto & partida : this->games) {
        mensaje.append("\n");
        mensaje.append(partida.second.information());
    }
    /*
     * send the Update with the data
     */
}

void GameManager::createGame(uint8_t idCreator, uint8_t capacityGame, const std::string& nameGame,
                             std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> startClientThreads) {
    std::unique_lock<std::mutex> lock(this->mutex);

    auto *queueGame = new BlockingQueue<Action*>;
    auto *pGame =  new Game(capacityGame,
                            nameGame,
                            queueGame);


    std::pair<std::map<std::string,Game&>::iterator,bool> ret;
    auto iter = games.insert(std::pair<std::string,Game&>(nameGame,*pGame));

    if (iter.second) {
        auto *queueSender = new BlockingQueue<Action*>;
        pGame->joinPlayer(idCreator,queueSender);
        startClientThreads(queueGame, queueSender);
    }
}

void
GameManager::joinGame(uint8_t idCreator, const std::string& nameGame, std::function<void(BlockingQueue<Action *> *,
                                                                                         BlockingQueue<Action *> *)> startClientThreads) {

    std::unique_lock<std::mutex> lock(this->mutex);

    auto iter = games.find(nameGame);

    if (iter->first == nameGame and not iter->second.isFull()) {
        auto *queueSender = new BlockingQueue<Action*>;
        iter->second->joinPlayer(idCreator,queueSender);
        startClientThreads(iter->second.getQueue(), queueSender);
    } else {

    }
}




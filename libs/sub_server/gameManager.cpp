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
/*
 * data en caso de creacion
 * [0] -> numero de jugadores
 * [1] -> primer char del nombre de partida
 * [n] -> comando NOP finaliza la data
 */
/*
void GameManager::createGame(uint8_t id,
                             uint8_t capacity,
                             ClientManager *pClientManager,
                             const std::string& name) {
    std::unique_lock<std::mutex> lock(this->mutex);

    auto *queueReceiver = new BlockingQueue<Action>;
    auto *pGame =  new Game(capacity,
                            name,
                            queueReceiver);


    std::pair<std::map<std::string,Game&>::iterator,bool> ret;
    auto iter = games.insert(std::pair<std::string,Game&>(name,*pGame));

    if (iter.second) {
        auto *queueSender = new BlockingQueue<Update>;
        pGame->joinPlayer(id,queueSender);
        pClientManager->setQueueReceiver(pGame->getQueue());
    }

}*/
/*
std::string GameManager::joinGame(uint8_t id, ClientManager *pManager, const std::string& name) {

    std::unique_lock<std::mutex> lock(this->mutex);
    auto iter = games.find(name);

    if (iter->first == name and iter->second.isFull()) {
        auto *queueSender = new BlockingQueue<Update>;
        iter->second.joinPlayer(id,queueSender);
        pManager->setQueueReceiver(iter->second.getQueue());
    } else {

    }
}*/

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
                             std::function<void(BlockingQueue<Action> *)> setQueue) {
    std::unique_lock<std::mutex> lock(this->mutex);

    auto *queueReceiver = new BlockingQueue<Action>;
    auto *pGame =  new Game(capacityGame,
                            nameGame,
                            queueReceiver);


    std::pair<std::map<std::string,Game&>::iterator,bool> ret;
    auto iter = games.insert(std::pair<std::string,Game&>(nameGame,*pGame));

    if (iter.second) {
        auto *queueSender = new BlockingQueue<Update>;
        pGame->joinPlayer(idCreator,queueSender);
        setQueue(queueReceiver);
    }
}

void
GameManager::joinGame(uint8_t idCreator, const std::string& nameGame, std::function<void(
        BlockingQueue<Action> *)> setQueue) {

    std::unique_lock<std::mutex> lock(this->mutex);

    auto iter = games.find(nameGame);

    if (iter->first == nameGame and iter->second.isFull()) {
        auto *queueSender = new BlockingQueue<Update>;
        iter->second.joinPlayer(idCreator,queueSender);
        setQueue(iter->second.getQueue());
    } else {

    }
}




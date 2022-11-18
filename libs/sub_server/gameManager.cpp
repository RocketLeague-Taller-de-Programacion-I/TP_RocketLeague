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
void GameManager::createGame(uint8_t id,
                             uint8_t capacity,
                             ClientManager *pClientManager,
                             const std::string& name) {
    std::unique_lock<std::mutex> lock(this->mutex);

    auto *queueReceiver = new BlockingQueue<Action>;
    auto *queueSender = new BlockingQueue<Update>;

    auto *pGame =  new Game(capacity,
                            name,
                            queueReceiver);


    std::pair<std::map<std::string,Game&>::iterator,bool> ret;
    games.insert(std::pair<std::string,
            Game&>(name,
                      *pGame));

    /*
     * Join Player
     */
    pGame->joinPlayer(id,queueSender);

    pClientManager->setQueue(queueReceiver, queueSender);
}

std::string GameManager::joinGame(std::vector<char> &data, ClientManager *pManager) {

    * std::unique_lock<std::mutex> lock(this->mutex);
    std::string aGameName(data.begin()+1,data.end());

    auto iter = games.find(aGameName);

     * iter es una tupla
     *      - en el primer elemento contiene la key encontrada
     *      - en el segundo el Game
     * Si first es igual a la key buscada y la partida tiene espacio
     * para nuevos jugadores, entonces puede hacer el Update

    if (iter->first == aGameName and iter->second.joinPlayer()) {

         * do update in Game

    } else {

         * not update

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




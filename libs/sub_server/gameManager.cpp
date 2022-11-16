//
// Created by lucaswaisten on 04/11/22.
//

#include <iostream>
#include "gameManager.h"

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
void GameManager::createGame(std::vector<char> &data, ClientManager *pManager) {
    /*
     * estoy deserealizanso y no le corresponde a monitor
     * puede ser el protocolo el que haga todo esto con la data
     */
    std::unique_lock<std::mutex> lock(this->mutex);

    std::string aGameName(data.begin()+1,data.end());
    auto *pGame =  new Game(data[0],
                            aGameName);

    std::pair<std::map<std::string,Game&>::iterator,bool> ret;
    ret = games.insert(std::pair<std::string,
            Game&>(aGameName,
                      *pGame));
    /*
     * if ret.second = true
     *  - Game tiene que crear un Update
     *  del tipo CREATE_ROOM y pasarle al manager
     *  este update para que lo pushee
     */
   if (ret.second) {
      /*
       * do game update
       */
   } else {
       /*
        * delete game and wherever
        */
       delete pGame;
   }
}

std::string GameManager::joinGame(std::vector<char> &data, ClientManager *pManager) {
    std::unique_lock<std::mutex> lock(this->mutex);
    std::string aGameName(data.begin()+1,data.end());

    auto iter = games.find(aGameName);
    /*
     * iter es una tupla
     *      - en el primer elemento contiene la key encontrada
     *      - en el segundo el Game
     * Si first es igual a la key buscada y la partida tiene espacio
     * para nuevos jugadores, entonces puede hacer el Update
     */
    if (iter->first == aGameName and iter->second.joinPlayer()) {
        /*
         * do update in Game
         */
    } else {
        /*
         * not update
         */
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
/*
 * Procesas las actiones move:
 * -left
 * -right
 * -down
 * -up
 * -jump
 * -turbo
 *
 * posible problema cuando tenga que decirle a que jugador mover
 */
std::string GameManager::move(std::vector<char> data, ClientManager *pManager) {
    /*
     * Hay que buscar la partida donde esta el cliente y hacer le update
     */
    return std::string();
}

void GameManager::sendUpdate(Update &update) {
    //
}




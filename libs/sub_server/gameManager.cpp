//
// Created by lucaswaisten on 04/11/22.
//

#include <iostream>
#include "gameManager.h"

#define OK_MSG "OK"
#define ERROR_MSG "ERROR"

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
std::string GameManager::createGame(std::vector<char> &data) {
    std::unique_lock<std::mutex> lock(this->mutex);

    std::string aGameName(data.begin()+1,data.end());
    auto *pGame =  new Game(data[0],
                            aGameName);

    std::pair<std::map<std::string,Game&>::iterator,bool> ret;
    ret = games.insert(std::pair<std::string,
            Game&>(aGameName,
                      *pGame));
    /*
     *
     */
    pGame->upDateAll();
   if (ret.second) {
       return OK_MSG;
   } else {
       delete pGame;
       return ERROR_MSG;
   }
}

std::string GameManager::joinGame(std::vector<char> &data) {
    std::unique_lock<std::mutex> lock(this->mutex);
    std::string aGameName(data.begin()+1,data.end());

    auto iter = games.find(aGameName);

    if (iter != games.end() and iter->second.joinPlayer()) {
        std::cout
                << "Comenzando partida "
                << aGameName
                << "..."
                << std::endl;
        return OK_MSG;
    } else {
        return ERROR_MSG;
    }
}

std::string GameManager::listGames() {
    std::unique_lock<std::mutex> lock(this->mutex);
    std::string mensaje("OK");

    for (auto & partida : this->games) {
        mensaje.append("\n");
        mensaje.append(partida.second.information());
    }
    return mensaje;
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
std::string GameManager::move(std::vector<char> data) {
    return std::string();
}

void GameManager::sendUpdate(Update &update) {
    //
}




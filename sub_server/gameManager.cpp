//
// Created by lucaswaisten on 04/11/22.
//

#include <iostream>
#include "gameManager.h"

#define OK_MSG 0
#define ERROR_MSG 1

void GameManager::cleanGames() {
    for (auto & game: games) {
        delete &game.second;
    }
}

uint8_t GameManager::createGame(uint8_t aCantPlayers, const std::string &aGameName) {
    std::unique_lock<std::mutex> lock(this->mutex);
    auto *pGame =  new Game(aCantPlayers,
                            aGameName);

    std::pair<std::map<std::string,Game&>::iterator,bool> ret;
    ret = games.insert(std::pair<std::string,
            Game&>(aGameName,
                      *pGame));

    if (ret.second) {
        return OK_MSG;
    } else {
        delete pGame;
        return ERROR_MSG;
    }
}

uint8_t GameManager::joinGame(const std::string &aGameName) {
    std::unique_lock<std::mutex> lock(this->mutex);
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



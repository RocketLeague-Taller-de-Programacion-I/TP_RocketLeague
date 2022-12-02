//
// Created by lucaswaisten on 04/11/22.
//

#include "gameManager.h"

bool GameManager::createGame(uint8_t idCreator, uint8_t capacityGame, const std::string &nameGame,
                             std::function<void(ProtectedQueue<std::shared_ptr<ServerAction>> *,
                                                BlockingQueue<std::shared_ptr<ServerUpdate>> *)> &startThreadsCallable) {
    std::unique_lock<std::mutex> lock(this->mutex);

    if (games.find(nameGame) == games.end()) {
        auto *queueGame = new ProtectedQueue<std::shared_ptr<ServerAction>>;
        games[nameGame] = new Game(capacityGame,nameGame,queueGame);
    } else {
        return false;
    }
    auto queueSender = new BlockingQueue<std::shared_ptr<ServerUpdate>>;
    games[nameGame]->joinPlayer(idCreator,queueSender);

    startThreadsCallable(games[nameGame]->getQueue(), queueSender);

    return true;
}
bool GameManager::joinGame(uint8_t idCreator, const std::string& nameGame, std::function<void(
        ProtectedQueue<std::shared_ptr<ServerAction>> *,
        BlockingQueue<std::shared_ptr<ServerUpdate>> *)> &startThreadsCallable) {

    std::unique_lock<std::mutex> lock(this->mutex);
    if (this->games[nameGame]->isFull()) {
        // TODO: return update with ERROR message
        return false;
    } else {
        auto queueSender = new BlockingQueue<std::shared_ptr<ServerUpdate>>;
        games[nameGame]->joinPlayer(idCreator,queueSender);

        startThreadsCallable(games[nameGame]->getQueue(), queueSender);
    }
    return true;
}

uint8_t GameManager::listGames(uint8_t &id, std::vector<uint8_t> &listData) {
    std::unique_lock<std::mutex> lock(this->mutex);
    if (this->games.empty()) { return 0; }

    for (auto & partida : this->games) {
        std::vector<uint8_t> data = partida.second->information();
        listData.insert(listData.end(), data.begin(), data.end());
    }
    return games.size();
}

void GameManager::cleanGames() {
    for (auto & game: games) {
        game.second->stop();
        delete game.second;
    }
}

void GameManager::deletePlayer(uint8_t idPlayer) {
    // search idPlayer on Games maps
    for (auto & game: games) {
        if (game.second->hasPlayer(idPlayer)) {
            game.second->deletePlayer(idPlayer);
            // if player was deleted, delete game if is empty
            if (game.second->isFinished()) {
                game.second->stop();
                delete game.second;
                games.erase(game.first);
            }
            break;
        }
    }
}





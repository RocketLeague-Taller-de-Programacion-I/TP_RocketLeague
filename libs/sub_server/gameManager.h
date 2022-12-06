
#ifndef ROCKETLEAGUE_GAMEMANAGER_H
#define ROCKETLEAGUE_GAMEMANAGER_H

#include <iostream>
#include <map>
#include <mutex>
#include <vector>
#include <functional>
#include "game.h"

class GameManager {
    std::mutex mutex;
    std::map<std::string, Game*> games;
public:
   uint8_t listGames(uint8_t &id, std::vector<uint8_t> &listData);
    bool createGame(uint8_t idCreator, uint8_t capacityGame,
                    const std::string& nameGame, std::function<void(ProtectedQueue<std::shared_ptr<ServerAction>> *,
                                                                    BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>> *)> &startThreadsCallable);
    bool joinGame(uint8_t idCreator, const std::string& nameGame, std::function<void(
            ProtectedQueue<std::shared_ptr<ServerAction>> *,
            BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>> *)> &startThreadsCallable);

    void cleanGames();

    void deletePlayer(uint8_t idPlayer);
};

#endif // ROCKETLEAGUE_GAMEMANAGER_H
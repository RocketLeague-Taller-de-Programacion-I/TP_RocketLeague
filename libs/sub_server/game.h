#ifndef ROCKETLEAGUE_GAME_H
#define ROCKETLEAGUE_GAME_H

#include <cstdint>
#include <string>
#include <map>
#include <atomic>
#include <unistd.h>

#include "sub_common/thread.h"
#include "sub_common/BlockingQueue.h"
#include "sub_common/ProtectedQueueBounded.h"
#include "sub_server/server_box2d/Match.h"

#include "server_updates/ServerUpdateWorld.h"
#include "server_updates/ServerStartedGameACK.h"
#include "server_actions/ServerActionMove.h"

class Game : public Thread {
private:
    Match match;
    int capacity;
    int playerOnLine;
    std::string gameName;
    bool closed;
    std::atomic<bool> finished;
    std::atomic<bool> gameStarted;

    std::map<uint8_t,BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>>*> mapSender;
    ProtectedQueue<std::shared_ptr<ServerAction>> *queue;

public:
    std::vector<uint8_t> information();
    void run() override;
    void stop() override;
    /*
    * No copiable
    */
    Game(const Game&) = delete;
    Game(int capacity, std::string  name, ProtectedQueue<std::shared_ptr<ServerAction>> *pQueue);

    ~Game() override;

    Game& operator=(const Game&) = delete;

    void joinPlayer(uint8_t& id, BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>> *sender);

    bool isFull() const;

    ProtectedQueue<std::shared_ptr<ServerAction>> * getQueue();
    void broadcastUpdate(std::optional<std::shared_ptr<ServerUpdate>> &update);

    bool hasPlayer(uint8_t idPlayer);
    void deletePlayer(uint8_t idPlayer);
    bool started() { return gameStarted; };
    bool isFinished() const;

    void broadcastUpdateForRepetition(ProtectedQueueBounded<std::optional<std::shared_ptr<ServerUpdate>>> &bounded);
};


#endif //ROCKETLEAGUE_GAME_H
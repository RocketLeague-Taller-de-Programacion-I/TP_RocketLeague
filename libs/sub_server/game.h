//
// Created by lucaswaisten on 04/11/22.
//

#ifndef ROCKETLEAGUE_GAME_H
#define ROCKETLEAGUE_GAME_H

#include <cstdint>
#include <string>
#include <map>
#include "sub_common/thread.h"
#include "sub_common/BlockingQueue.h"
#include "sub_server/server_box2d/Match.h"

#include "server_updates/ServerUpdateWorld.h"
#include "server_updates/ServerStartedGameACK.h"
#include "server_actions/ServerAction.h"
#include "server_actions/ServerActionMove.h"

typedef uint8_t idPlayer_t;

class Game : public Thread {
private:
    Match match;
    int capacity;
    int playerOnLine;
    std::string gameName;
    bool closed;

    std::map<uint8_t ,BlockingQueue<std::shared_ptr<ServerUpdate>>*> mapSender;
    //map {id, BlockingQueue<ServerUpdate*>}

    ProtectedQueue<ServerAction *> *queue;
    //BlockingQueue<ServerAction*> *queue;
public:
    std::vector<uint8_t> information();

    void run() override;
    void stop() override;
    /*
    * No copiable
    */
    Game(const Game&) = delete;
    Game(int capacity, std::string  name, ProtectedQueue<ServerAction *> *pQueue);
    ~Game() override;

    Game& operator=(const Game&) = delete;

    void joinPlayer(uint8_t& id, BlockingQueue<std::shared_ptr<ServerUpdate>> *sender);

    bool isFull() const;

    ProtectedQueue<ServerAction *> * getQueue();

    void broadcastUpdate(const std::shared_ptr<ServerUpdate>& update);
    void brodcastUpdateGameEvents(std::vector<ServerUpdate *> updates);
};


#endif //ROCKETLEAGUE_GAME_H
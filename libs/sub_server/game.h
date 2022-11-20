//
// Created by lucaswaisten on 04/11/22.
//

#ifndef ROCKETLEAGUE_GAME_H
#define ROCKETLEAGUE_GAME_H


#include <cstdint>
#include <string>
#include "sub_common/thread.h"
#include "sub_common/BlockingQueue.h"
#include "Match.h"
#include "sub_common/sub_action/Action.h"
#include "sub_common/sub_action/ActionUpdate.h"

typedef uint8_t idPlayer_t;

class Action;

class Game : public Thread {
private:
    Match match;
    int capacity;
    int playerOnLine;
    std::string gameName;
    bool closed;

    std::map<uint8_t ,BlockingQueue<Action*>*> mapSender;
    BlockingQueue<Action*> *queue;
public:
    std::string information();

    void run() override;
    void stop() override;
    /*
    * No copiable
    */
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void joinPlayer(uint8_t i, BlockingQueue<Action*> *sender);

    bool isFull() const;

    //Game(uint8_t &capacity, std::string &name, BlockingQueue<Action *> *pQueue);

    BlockingQueue<Action *> * getQueue();


    Game(uint8_t &aCapacity, const std::string &aName, BlockingQueue<Action *> *pQueue);

    void updateClientSender(ActionUpdate *update);
};


#endif //ROCKETLEAGUE_GAME_H

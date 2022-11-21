//
// Created by lucaswaisten on 04/11/22.
//

#ifndef ROCKETLEAGUE_GAME_H
#define ROCKETLEAGUE_GAME_H
class Action;
#include <cstdint>
#include <string>
#include <map>
#include "sub_common/thread.h"
#include "sub_common/BlockingQueue.h"

typedef uint8_t idPlayer_t;

class Game : public Thread {
private:
    uint8_t capacity;
    int playerOnLine;
    std::string gameName;
    //std::map<uint8_t ,BlockingQueue<Action>&> mapReceiver;
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
    Game(uint8_t capacity, std::string  name, BlockingQueue<Action *> *pQueue);

    Game& operator=(const Game&) = delete;

    void joinPlayer(uint8_t id, BlockingQueue<Action*> *sender);

    bool isFull() const;

    BlockingQueue<Action *> * getQueue();
    void broadcastUpdate(Action* update);
    void broadcastUpdate(Action* update, uint8_t id);

    void brodcastUpdates(std::vector<Action *> updates);
};


#endif //ROCKETLEAGUE_GAME_H

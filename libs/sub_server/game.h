//
// Created by lucaswaisten on 04/11/22.
//

#ifndef ROCKETLEAGUE_GAME_H
#define ROCKETLEAGUE_GAME_H


#include <cstdint>
#include <string>
#include "sub_common/thread.h"
#include "sub_common/BlockingQueue.h"
#include "sub_common/Action.h"
#include "sub_common/Update.h"

typedef uint8_t idPlayer_t;

class Game : public Thread {
private:
    int capacity;
    int playerOnLine;
    std::string gameName;
    std::map<uint8_t ,BlockingQueue<Action>&> mapReceiver;
    std::map<uint8_t ,BlockingQueue<Update>&> mapSender;
public:
    Game(uint8_t aCant, std::string  aName);

   // bool joinPlayer();

    std::string information();

    void run() override;

    /*
    * No copiable
    */
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void joinPlayer(uint8_t i, BlockingQueue<Action> &receiver, BlockingQueue<Update> &sender);

    bool isFull() const;
};


#endif //ROCKETLEAGUE_GAME_H

//
// Created by lucaswaisten on 04/11/22.
//

#ifndef ROCKETLEAGUE_GAME_H
#define ROCKETLEAGUE_GAME_H


#include <cstdint>
#include <string>

class Game {
private:
    int capacity;
    int playerOnLine;
    std::string gameName;
public:
    Game(uint8_t aCant, std::string  aName);

    bool joinPlayer();

    std::string information();

    /*
    * No copiable
    */
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
};


#endif //ROCKETLEAGUE_GAME_H

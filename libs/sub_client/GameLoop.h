//
// Created by franco on 03/11/22.
//

#ifndef ROCKETLEAGUE_GAMELOOP_H
#define ROCKETLEAGUE_GAMELOOP_H

#include "SDL2pp/SDL2pp.hh"
#include "Player.h"

class GameLoop {
    SDL2pp::Renderer &renderer;
    Player player;
    bool running;
    int xMax;
    int yMax;
    bool handle_events();
    void update(float dt);
    void render();

public:
    GameLoop(SDL2pp::Renderer &renderer, SDL2pp::Texture &texture, int xMax, int yMax);
    void run();
};
#endif //ROCKETLEAGUE_GAMELOOP_H

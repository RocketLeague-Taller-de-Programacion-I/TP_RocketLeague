//
// Created by franco on 03/11/22.
//

#ifndef ROCKETLEAGUE_GAMELOOP_H
#define ROCKETLEAGUE_GAMELOOP_H

#include "SDL2pp/SDL2pp.hh"
#include "Player.h"
#include "sub_common/Action.h"
#include "sub_common/BlockingQueue.h"
#include "sub_common/protocolo.h"

class GameLoop {
    SDL2pp::Renderer &renderer;
    Player player;
    BlockingQueue<Action*>& updatesQueue;
    BlockingQueue<Action*>& actionsQueue;
    bool running;
    int xMax;
    int yMax;
    bool handle_events();
    void update(float dt);
    void render();

public:
    GameLoop(SDL2pp::Renderer &renderer, SDL2pp::Texture &texture, int xMax, int yMax, BlockingQueue<Action *> &updates,
             BlockingQueue<Action *> &actions);

    void run();
};
#endif //ROCKETLEAGUE_GAMELOOP_H

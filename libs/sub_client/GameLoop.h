//
// Created by franco on 03/11/22.
//

#ifndef ROCKETLEAGUE_GAMELOOP_H
#define ROCKETLEAGUE_GAMELOOP_H

#include "SDL2pp/SDL2pp.hh"
#include "Player.h"
#include "GameUpdate.h"
#include "ClientAction.h"
#include "sub_common/ProtectedQueue.h"
#include "Worldview.h"

class GameLoop {
    SDL2pp::Renderer &renderer;
    ProtectedQueue<GameUpdate*>& updatesQueue;
    BlockingQueue<ClientAction*>& actionsQueue;
    bool running;
    int xMax;
    int yMax;
    bool handle_events();
    void update(float dt);
    void render();
public:
    GameLoop(SDL2pp::Renderer &renderer, int xMax, int yMax, ProtectedQueue<GameUpdate*> &updates,
             BlockingQueue<ClientAction*> &actions, Worldview &wv);

    void run();
private:
    Worldview &wv;
};
#endif //ROCKETLEAGUE_GAMELOOP_H

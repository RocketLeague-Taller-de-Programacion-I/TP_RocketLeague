//
// Created by franco on 03/11/22.
//

#ifndef ROCKETLEAGUE_GAMELOOP_H
#define ROCKETLEAGUE_GAMELOOP_H

#include "SDL2pp/SDL2pp.hh"
#include "Player.h"
#include "sub_client/client_updates/ClientUpdate.h"
#include "sub_client/client_actions/ClientAction.h"
#include "sub_common/ProtectedQueue.h"
#include "sub_common/BlockingQueue.h"
#include "Worldview.h"

#define NOP 10
class GameLoop {
    SDL2pp::Renderer &renderer;
    ProtectedQueue<ClientUpdate*>& updatesQueue;
    BlockingQueue<ClientAction*>& actionsQueue;
    bool running;
    int xMax;
    int yMax;
    bool handle_events();
    void update(float dt);
    void render();
public:
    GameLoop(SDL2pp::Renderer &renderer, int xMax, int yMax, ProtectedQueue<ClientUpdate*> &updates,
             BlockingQueue<ClientAction*> &actions, Worldview &wv);

    void run();
private:
    Worldview &wv;
    std::unordered_map<uint32_t ,uint8_t> directionMap = {
            {SDLK_LEFT,LEFT_D},
            {SDLK_RIGHT,RIGHT_D},
            {SDLK_UP,JUMP_D},
            {SDLK_DOWN,DOWN_D},
            {SDLK_ESCAPE,NOP}
    };
};
#endif //ROCKETLEAGUE_GAMELOOP_H

//
// Created by franco on 03/11/22.
//

#ifndef ROCKETLEAGUE_GAMELOOP_H
#define ROCKETLEAGUE_GAMELOOP_H

#include "SDL2pp/SDL2pp.hh"

#include "sub_common/ProtectedQueue.h"
#include "sub_common/BlockingQueue.h"

#include "sub_client/ClientProtocol.h"

#include "sub_client/client_updates/ClientUpdateWorld.h"
#include "sub_client/client_actions/ClientActionMove.h"

#include "Worldview.h"
#include "Player.h"

class GameLoop {
private:
    const std::unordered_map<SDL_Keycode , uint8_t> mapSDLKey = {
            {SDLK_RIGHT, RIGHT},
            {SDLK_LEFT, LEFT},
            {SDLK_UP, JUMP},
            {SDLK_DOWN, DOWN},
            {SDLK_SPACE, TURBO}
    };
    uint8_t id;
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
    GameLoop(uint8_t &id, SDL2pp::Renderer &renderer, int xMax, int yMax, ProtectedQueue<ClientUpdate *> &updates,
             BlockingQueue<ClientAction *> &actions, Worldview &wv);

    void run();
private:
    Worldview &wv;

    void popUpdates();
};
#endif //ROCKETLEAGUE_GAMELOOP_H

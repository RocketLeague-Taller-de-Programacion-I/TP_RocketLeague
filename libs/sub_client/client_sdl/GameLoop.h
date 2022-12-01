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

class GameLoop {
    SDL2pp::Renderer &renderer;
    ProtectedQueue<std::shared_ptr<ClientUpdate>>& updatesQueue;
    BlockingQueue<std::shared_ptr<ClientAction>>& actionsQueue;
    bool running;
    int xMax;
    int yMax;
    bool handle_events();
    void update(float dt);
    void render();
public:
    GameLoop(uint8_t &id, SDL2pp::Renderer &renderer, int xMax, int yMax,
             ProtectedQueue<std::shared_ptr<ClientUpdate>> &updates,
             BlockingQueue<std::shared_ptr<ClientAction>> &actions, Worldview &wv);

    void run();
private:
    uint8_t &id;

    Worldview &wv;

    std::unordered_map<uint32_t ,uint8_t> directionMap = {
            {SDLK_RIGHT,RIGHT_D},
            {SDLK_LEFT,LEFT_D},
            {SDLK_UP,JUMP_D},
            {SDLK_DOWN,DOWN_D},
            {SDLK_ESCAPE,TURBO_D}
    };

    void popUpdates();
};
#endif //ROCKETLEAGUE_GAMELOOP_H

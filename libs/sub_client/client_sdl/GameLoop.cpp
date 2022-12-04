//
// Created by franco on 03/11/22.
//

#include <unistd.h>
#include "GameLoop.h"
#include "sub_client/client_actions/ClientActionMove.h"
#include "Ball.h"
#include "Score.h"
#include "sub_client/client_updates/ClientUpdateWorld.h"

#define EVENTS_X_FRAME 10

GameLoop::GameLoop(uint8_t &id, SDL2pp::Renderer &renderer, int xMax, int yMax,
                   ProtectedQueue<std::shared_ptr<ClientUpdate>> &updates,
                   BlockingQueue<std::optional<std::shared_ptr<ClientAction>>> &actions, Worldview &wv)
        : id(id),
          renderer(renderer),
          updatesQueue(updates),
          actionsQueue(actions),
          running(true),
          xMax(xMax),
          yMax(yMax),
          wv(wv){}

void GameLoop::run() {
    while (running) {
        handle_events();
        //pop from updates queue
        popUpdates();
        update(FRAME_RATE);
        render();
        // la cantidad de segundos que debo dormir se debe ajustar en función
        // de la cantidad de tiempo que demoró el handleEvents y el render
        usleep(FRAME_RATE);
    }
}

bool GameLoop::handle_events() {
    SDL_Event event;

    for (int i = 0; i < EVENTS_X_FRAME; ++i) {
        if(!SDL_PollEvent(&event)) {
            continue;
        }
        switch(event.type) {
            case SDL_KEYDOWN:
                {
                    //catch every other key down that is not in the map
                    if(directionMap.count(event.key.keysym.sym) == 0) {
                        continue;
                    }
                    //if the key is already down, do nothing
                    if(keyDownStateMap[event.key.keysym.sym]) {
                        continue;
                    }
                    std::cout << "key down: " << (int) keyDownStateMap[event.key.keysym.sym] << std::endl;

                    uint8_t movement = directionMap.at(event.key.keysym.sym);
                    std::shared_ptr<ClientAction> action = std::make_shared<ClientActionMove>(id, movement, ON);
                    std::optional<std::shared_ptr<ClientAction>> optAction = action;
                    actionsQueue.push(optAction);

                    // set the key down state to true
                    keyDownStateMap[event.key.keysym.sym] = true;
                }
                break;
            case SDL_KEYUP:
                {
                    if(directionMap.count(event.key.keysym.sym) == 0) {
                        continue;
                    }

                    uint8_t movement = directionMap.at(event.key.keysym.sym);
                    std::shared_ptr<ClientAction> action = std::make_shared<ClientActionMove>(id, movement, OFF);
                    std::optional<std::shared_ptr<ClientAction>> optAction = action;
                    actionsQueue.push(optAction);
                    std::cout << "key up: " << (int) keyDownStateMap[event.key.keysym.sym] << std::endl;

                    keyDownStateMap[event.key.keysym.sym] = false;
                }
                break;

            case SDL_QUIT:
                running = false;
                break;
        }
    }
    return true;
}

void GameLoop::render() {
    renderer.SetDrawColor(0x00, 0x00, 0x00);
    renderer.Clear();
    wv.render(renderer);
    renderer.Present();
}

void GameLoop::popUpdates() {
    std::queue<std::shared_ptr<ClientUpdate>> updates = updatesQueue.popAll();

    std::shared_ptr<ClientUpdate> update;

    while(!updates.empty()) {
        update = updates.front();
        Ball ball = update->getBall();
        Score score = update->getScore();
        std::vector<Car> cars = update->getCars();
        wv.updateSprites(ball, score, cars);
        updates.pop();
    }
}
void GameLoop::update(float dt) {
//    wv.update(dt);
}

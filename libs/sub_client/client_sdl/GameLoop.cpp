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

GameLoop::GameLoop(SDL2pp::Renderer &renderer, int xMax, int yMax, ProtectedQueue<std::shared_ptr<ClientUpdate>> &updates,
                   BlockingQueue<std::shared_ptr<ClientAction>> &actions, Worldview &wv)
        : renderer(renderer),
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

    for (int i = 0; i < EVENTS_X_FRAME and SDL_PollEvent(&event) ; ++i) {
        switch(event.type) {
            case SDL_KEYDOWN: {
                // ¿Qué pasa si mantengo presionada la tecla?
                auto &keyEvent = (SDL_KeyboardEvent&) event;
                if(keyEvent.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                    break;
                }
                uint8_t movement = directionMap.at(keyEvent.keysym.sym);
                std::shared_ptr<ClientAction> action = std::make_shared<ClientActionMove>(movement,ON);
                actionsQueue.push(action);
            } // Fin KEY_DOWN
                break;
            case SDL_KEYUP: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;

                uint8_t movement = directionMap.at(keyEvent.keysym.sym);
                std::shared_ptr<ClientAction> action = std::make_shared<ClientActionMove>(movement,OFF);
                actionsQueue.push(action);
            }// Fin KEY_UP
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
    //    player.render(renderer);
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
    wv.update(dt);
}
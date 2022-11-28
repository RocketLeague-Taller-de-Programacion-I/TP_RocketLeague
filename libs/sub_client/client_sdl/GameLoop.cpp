//
// Created by franco on 03/11/22.
//

#include <map>
#include <unistd.h>
#include "GameLoop.h"
#include "sub_client/client_actions/ClientActionMove.h"
#include "Ball.h"
#include "Score.h"
#include "sub_client/client_updates/ClientUpdateWorld.h"

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
    // Gameloop, notar como tenemos desacoplado el procesamiento de los inputs (handleEvents)
    // del update del modelo.
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

    while(SDL_PollEvent(&event)){
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
        } // fin switch(event)
    } // fin while(SDL_PollEvents)
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
    // TODO: implement swap between queues
    std::shared_ptr<ClientUpdate> update;
    while (!updatesQueue.tryPop(update)) {
        Ball ball = update->getBall();
        std::cout << "Ball: " << (int)ball.getX() << " " << (int)ball.getY() << std::endl;
        Score score = update->getScore();
        std::cout << "Score: " << (int)score.getLocal() << " " << (int)score.getVisitor() << std::endl;

        std::vector<Car> players = update->getCars();
        for (auto &player : players) {
            std::cout << "Player: " << (int)player.getX() << " " << (int)player.getY() << std::endl;
        }
    }
}
void GameLoop::update(float dt) {
    wv.update(dt);
}

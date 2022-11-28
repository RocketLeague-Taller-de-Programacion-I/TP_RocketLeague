//
// Created by franco on 03/11/22.
//

#include <map>
#include <utility>
#include <unistd.h>
#include "GameLoop.h"

GameLoop::GameLoop(uint8_t &id, SDL2pp::Renderer &renderer, int xMax, int yMax, ProtectedQueue<ClientUpdate *> &updates,
                   BlockingQueue<ClientAction *> &actions, Worldview &wv)
        : id(id),
          renderer(renderer),
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
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                if(keyEvent.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                        break;
                }
                uint8_t movement = mapSDLKey.at(keyEvent.keysym.sym);
                ClientAction* action = new ClientActionMove(movement, ON);
                actionsQueue.push(action);
            } // Fin KEY_DOWN
                break;
            case SDL_KEYUP: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;

                uint8_t movement = mapSDLKey.at(keyEvent.keysym.sym);
                ClientAction* action = new ClientActionMove(movement, OFF);
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
//        player.render(renderer);
    renderer.Present();
}

void GameLoop::update(float dt) {
    wv.update(dt);
}

void GameLoop::popUpdates() {
    ClientUpdate* update;
    while (!updatesQueue.tryPop(update)) {
        Ball ball = dynamic_cast<ClientUpdateWorld*>(update)->getBall();
        std::cout << "Ball: " << (int)ball.getX() << " " << (int)ball.getY() << std::endl;
        Score score = dynamic_cast<ClientUpdateWorld*>(update)->getScore();
        std::cout << "Score: " << (int)score.getLocal() << " " << (int)score.getVisitor() << std::endl;

        std::vector<Car> players = dynamic_cast<ClientUpdateWorld*>(update)->getCars();
        for (auto &player : players) {
            std::cout << "Player: " << (int)player.getX() << " " << (int)player.getY() << std::endl;
        }
        delete update;
    }
}

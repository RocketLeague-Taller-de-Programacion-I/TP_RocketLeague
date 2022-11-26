//
// Created by franco on 03/11/22.
//

#include <map>
#include <utility>
#include <unistd.h>
#include "GameLoop.h"

GameLoop::GameLoop(SDL2pp::Renderer &renderer, int xMax, int yMax, ProtectedQueue<ClientUpdate*> &updates,
                   BlockingQueue<ClientAction*> &actions, Worldview &wv)
        : renderer(renderer),
          updatesQueue(updates),
          actionsQueue(actions),
          running(true),
          xMax(xMax),
          yMax(yMax),
          wv(wv){}

// falta el loop a tiempo constante
void GameLoop::run() {
    // Gameloop, notar como tenemos desacoplado el procesamiento de los inputs (handleEvents)
    // del update del modelo.
    while (running) {
        handle_events();
        //pop from updates queue
        update(FRAME_RATE);
        render();
        // la cantidad de segundos que debo dormir se debe ajustar en función
        // de la cantidad de tiempo que demoró el handleEvents y el render
        usleep(FRAME_RATE);
    }
}

bool GameLoop::handle_events() {
    SDL_Event event;
    // Para el alumno: Buscar diferencia entre waitEvent y pollEvent
    // Aca estara la cola de eventos!!

    /*
     * Podrian leer una cantidad N de eventos por frame (por decir algo, 10)
     * para que no les quede tan limitada la cantidad de acciones que se pueden hacer en un frame
     * (sería loopear esto N veces...)
     */
    while(SDL_PollEvent(&event)){
        switch(event.type) {
            case SDL_KEYDOWN: {
                // ¿Qué pasa si mantengo presionada la tecla?
                // mantener presionada la tecla es otro tipo de evento (no se va a volver a disparar un key down)
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
//                        player.moveLeft(this->xMax);
                        break;
                    case SDLK_RIGHT:
//                        player.moveRight(this->xMax);
                        break;
                    case SDLK_UP:
//                        player.moveUp(this->yMax);
                        break;
                    case SDLK_DOWN:
//                        player.moveDown(this->yMax);
                        break;
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                }
//                std::vector<uint8_t> movement(1);
//                movement[0] = protocolo.getMapCommand(keyEvent.keysym.sym);
//                Action action(MOVE,movement);
//                actionsQueue.push(action);
            } // Fin KEY_DOWN
                break;
            case SDL_KEYUP: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
//                        player.stopMovingX();
                        break;
                    case SDLK_RIGHT:
//                        player.stopMovingX();
                        break;
                    case SDLK_UP:
//                        player.stopMovingY();
                        break;
                    case SDLK_DOWN:
//                        player.stopMovingY();
                        break;
                }
                // poppear de la cola de updatesQueue
                std::cout << "update to be popped of type: MOVE and data: " << std::endl;
            }// Fin KEY_UP
            case SDLK_ESCAPE:
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

void GameLoop::update(float dt) {
    wv.update(dt);
}

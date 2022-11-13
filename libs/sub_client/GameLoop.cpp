//
// Created by franco on 03/11/22.
//

#include <map>
#include <unistd.h>
#include "GameLoop.h"
#include "sub_common/BlockingQueue.h"
#include "sub_common/Action.h"

GameLoop::GameLoop(SDL2pp::Renderer &renderer, SDL2pp::Texture &texture, int xMax, int yMax,
                   BlockingQueue<std::string> &actions, BlockingQueue<std::string> &updates)
                   : renderer(renderer),
                   player(texture),
                   running(true),
                   xMax(xMax),
                   yMax(yMax){}

void GameLoop::run() {
    // Gameloop, notar como tenemos desacoplado el procesamiento de los inputs (handleEvents)
    // del update del modelo.
    while (running) {
        handle_events();
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
    while(SDL_PollEvent(&event)){
        std::string action;
        std::string update;
        switch(event.type) {
            case SDL_KEYDOWN: {
                // ¿Qué pasa si mantengo presionada la tecla?
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        player.moveLeft(this->xMax);
                        // cola_cliente.push(evento)
                        // create action
                        Action action1 = Action(MOVE,"moveLeft");
                        action = "moveLeft";
                        // push action to queue
                         actions.push(action);
                        break;
                    case SDLK_RIGHT:
                        player.moveRight(this->xMax);
                        // create action
                        Action action2 = Action(MOVE,"moveRight");
                        action= "moveRight";
                        // push action to queue
                        actions.push(action);

                        break;
                    case SDLK_UP:
                        player.moveUp(this->yMax);
                        // cola_cliente.push(evento)
                        // create action
                        Action action3 = Action(MOVE,"moveUp");
                        action = "moveUp";
                        // push action to queue
                        actions.push(action);
                        break;
                    case SDLK_DOWN:
                        player.moveDown(this->yMax);
                        // cola_cliente.push(evento)
                        // create action
                        Action action4 = Action(MOVE,"moveDown");
                        action = "moveDown";
                        // push action to queue
                        actions.push(action);
                        break;
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                }
            } // Fin KEY_DOWN
                break;
            case SDL_KEYUP: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        player.stopMovingX();
                        // poppear de la cola de updates
                        actions.tryPop(update);
                        std::cout << "update popped: " << update << std::endl;
                        break;
                    case SDLK_RIGHT:
                        player.stopMovingX();
                        // poppear de la cola de updates
                        actions.tryPop(update);
                        std::cout << "update popped: " << update << std::endl;
                        break;
                    case SDLK_UP:
                        player.stopMovingY();
                        // poppear de la cola de updates
                        actions.tryPop(update);
                        std::cout << "update popped: " << update << std::endl;
                        break;
                    case SDLK_DOWN:
                        player.stopMovingY();
                        // poppear de la cola de updates
                        actions.tryPop(update);
                        std::cout << "update popped: " << update << std::endl;
                        break;
                }
            }// Fin KEY_UP
        } // fin switch(event)
    } // fin while(SDL_PollEvents)
    return true;
}

void GameLoop::render() {
    renderer.SetDrawColor(0x00, 0x00, 0x00);
    renderer.Clear();
    player.render(renderer);
    renderer.Present();
}

void GameLoop::update(float dt) {
    player.update(dt);
}
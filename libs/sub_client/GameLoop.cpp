//
// Created by franco on 03/11/22.
//

#include <map>
#include <unistd.h>
#include "GameLoop.h"
#include "sub_common/protocolo.h"

GameLoop::GameLoop(SDL2pp::Renderer &renderer, SDL2pp::Texture &texture, int xMax, int yMax,
                   BlockingQueue<Action> &actions, BlockingQueue<Action> &updates)
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
        Protocolo protocolo;
        std::vector<char> movement(1);
        Action action(MOVE,movement);
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
                        movement[0] = protocolo.serializeAction(SDLK_LEFT);
                        // push action to queue
                         actions.push(action);
                        break;
                    case SDLK_RIGHT:
                        player.moveRight(this->xMax);
                        // create action
                        movement[0] = protocolo.serializeAction(SDLK_RIGHT);
                        // push action to queue
                        actions.push(action);
                        break;
                    case SDLK_UP:
                        player.moveUp(this->yMax);
                        // create action
                        movement[0] = protocolo.serializeAction(SDLK_UP);
                        // push action to queue
                        actions.push(action);
                        break;
                    case SDLK_DOWN:
                        player.moveDown(this->yMax);
                        // create action
                        movement[0] = protocolo.serializeAction(SDLK_DOWN);
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
                        std::cout << "update popped of type: MOVE and data: " << actions.pop().data.back() << std::endl;
                        break;
                    case SDLK_RIGHT:
                        player.stopMovingX();
                        // poppear de la cola de updates
                        std::cout << "update popped of type: MOVE and data: " << actions.pop().data.back() << std::endl;
                        break;
                    case SDLK_UP:
                        player.stopMovingY();
                        // poppear de la cola de updates
                        std::cout << "update popped of type: MOVE and data: " << actions.pop().data.back() << std::endl;
                        break;
                    case SDLK_DOWN:
                        player.stopMovingY();
                        // poppear de la cola de updates
                        std::cout << "update popped of type: MOVE and data: " << actions.pop().data.back() << std::endl;
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
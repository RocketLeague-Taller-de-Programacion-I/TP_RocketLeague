//
// Created by franco on 03/11/22.
//

#include <map>
#include <unistd.h>
#include "GameLoop.h"

GameLoop::GameLoop(SDL2pp::Renderer &renderer, SDL2pp::Texture &texture): renderer(renderer),
                                                                          player(texture),running(true){}

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

void GameLoop::handle_events() {
    SDL_Event event;
    // Para el alumno: Buscar diferencia entre waitEvent y pollEvent
    // Aca estara la cola de eventos!!
    while(SDL_PollEvent(&event)){
        switch(event.type) {
            case SDL_KEYDOWN: {
                // ¿Qué pasa si mantengo presionada la tecla?
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        player.moveLeft();
                        // cola_cliente.push(evento)
                        break;
                    case SDLK_RIGHT:
                        player.moveRight();
                        break;
                    case SDLK_UP:
                        player.moveUp();
                        // cola_cliente.push(evento)
                        break;
                    case SDLK_DOWN:
                        player.moveDown();
                        break;
                }
            } // Fin KEY_DOWN
                break;
            case SDL_KEYUP: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        player.stopMoving();
                        break;
                    case SDLK_RIGHT:
                        player.stopMoving();
                        break;
                }
            }// Fin KEY_UP
                break;
        } // fin switch(event)
    } // fin while(SDL_PollEvents)
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
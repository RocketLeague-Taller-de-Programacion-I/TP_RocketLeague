//
// Created by franco on 24/10/22.
//

#include <iostream>
#include "Client.h"
#include "mainwindow.h"
#include <cmath>
#include <iostream>
#include "GameLoop.h"
#include <QApplication>
#include <QLabel>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDLImage.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Surface.hh>
#include <SDL.h>
#include <QPushButton>
#include <QVBoxLayout>

using namespace SDL2pp;
#define TESTDATA_DIR "../libSDL2pp/testdata"
static const float pi = 3.14159265358979323846f;
Client::Client() {
    //qt_init(argc, argv);
}

Client::~Client() { }

void Client::view_screen() {
// Initialize SDL library
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    SDL2pp::Window sdlWindow("Hello world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                             800, 600,
                             SDL_WINDOW_RESIZABLE);

    // Creo renderer
    SDL2pp::Renderer renderer(sdlWindow, -1, SDL_RENDERER_SOFTWARE);

    // Encapsular en un repositorio de texturas para no crear multiples veces la misma textura
    SDL2pp::Texture im(renderer,
                       SDL2pp::Surface("assets/soldier2.png").SetColorKey(true, 0));

    GameLoop gameloop(renderer, im);
    gameloop.run();
}
int Client::qt_init(int argc, char *argv[]) {
    QApplication app(argc, argv);
    mainwindow window;
    window.show();
    return app.exec();
}
void Client::start() {
    // qt_init(0, nullptr);
    //view_screen();
}

//
// Created by franco on 24/10/22.
//

#include <iostream>
#include "Client.h"
#include "GameLoop.h"
#include "mainwindow.h"
#include <cmath>
#include <iostream>
#include <QApplication>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDLImage.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Surface.hh>
#include <SDL.h>

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
    SDL2pp::Window sdlWindow("RocketLeague", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                             800, 600,
                             SDL_WINDOW_RESIZABLE);

    // Creo renderer
    SDL2pp::Renderer renderer(sdlWindow, -1, SDL_RENDERER_SOFTWARE);

    // Encapsular en un repositorio de texturas para no crear multiples veces la misma textura
    SDL2pp::Texture im(renderer,
                       SDL2pp::Surface("../images/car.jpeg").SetColorKey(true, 0));

    GameLoop gameloop(renderer, im);
    gameloop.run();
}
int Client::qt_init(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    mainWindow.displayMainMenu();
    return app.exec();
}

void Client::start(int argc, char *argv[]) {
    try {
        // Clase que contiene el loop principal
        QApplication app(argc, argv);
        // Instancio la ventana principal
        MainWindow mainWindow;
        mainWindow.show();
        mainWindow.displayMainMenu();
        /*
         * QApplication::exec inicia el event loop y se queda esperando que finalice la aplicación. Cuando el usuario
         * realice una acción que haga un exit de QT, entonces esta función retorna (con el código de error
         * si lo hubo) y entonces se podrá crear la ventana de SDL.
         */
        // exec es una función bloqueante, cuando QT finaliza su ejecución, se realiza un return con el codigo de error
        int qt_return = app.exec();
        if (qt_return) {
            throw std::runtime_error("La aplicación QT finalizó de forma incorrecta");
        }
        std::cout << "QT finalizó correctamente con: " << qt_return << std::endl;
        // Initialize SDL library
        SDL2pp::SDL sdl(SDL_INIT_VIDEO);
        SDL2pp::Window sdlWindow("RocketLeague", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                 800, 600,
                                 SDL_WINDOW_RESIZABLE);

        // Creo renderer
        SDL2pp::Renderer renderer(sdlWindow, -1, SDL_RENDERER_SOFTWARE);

        // Encapsular en un repositorio de texturas para no crear multiples veces la misma textura
        SDL2pp::Texture im(renderer,
                           SDL2pp::Surface("../images/car.jpeg").SetColorKey(true, 0));

        GameLoop gameloop(renderer, im);
        gameloop.run();

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en la función main" << std::endl;
    }
}

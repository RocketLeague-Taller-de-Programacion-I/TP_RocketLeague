// Copyright 2022 Sprenger Roberta

#include <QApplication>
#include "RenderThread.h"

RenderThread::RenderThread(BlockingQueue<Action> &updates, BlockingQueue<Action>& actionsQueue)
        : updatesQueue(updates)
        , actionsQueue(actionsQueue){}

void RenderThread::run() {
    try {
        // Clase que contiene el loop principal
        int argc = 0;
        QApplication app(argc, nullptr);
        // Instancio la ventana principal
        MainWindow mainWindow(nullptr, updatesQueue, actionsQueue);
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
        // Initialize SDL library
        std::cout << "QT finalizó correctamente con: " << qt_return << std::endl;

        SDL2pp::SDL sdl(SDL_INIT_VIDEO);
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);
        auto Width = DM.w;
        auto Height = DM.h;
        SDL2pp::Window sdlWindow("RocketLeague", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                 Width, Height,
                                 SDL_WINDOW_RESIZABLE);

        // Creo renderer
        SDL2pp::Renderer renderer(sdlWindow, -1, SDL_RENDERER_SOFTWARE);

        // Encapsular en un repositorio de texturas para no crear multiples veces la misma textura
        SDL2pp::Texture im(renderer,
                           SDL2pp::Surface("../images/car.jpeg").SetColorKey(true, 0));

        GameLoop gameloop(renderer, im, Width, Height, updatesQueue, actionsQueue);
        gameloop.run();

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en la función main" << std::endl;
    }
}

//  Closes the accepting socket and forces all the client managers to finish
void RenderThread::stop() {
}

RenderThread::~RenderThread() = default;

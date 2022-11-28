// Copyright 2022 Sprenger Roberta

#include <QApplication>
#include "RenderThread.h"
#include "sub_client/client_sdl/Worldview.h"
using namespace SDL2pp;

RenderThread::RenderThread(ProtectedQueue<ClientUpdate*> &updates, BlockingQueue<ClientAction *> &actionsQueue)
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

        // exec es una función bloqueante, cuando QT finaliza su ejecución, se realiza un return con el codigo de error
        int qt_return = app.exec();
        if (qt_return) {
            throw std::runtime_error("La aplicación QT finalizó de forma incorrecta");
        }

        // Initialize SDL library
        std::cout << "QT finalizó correctamente con: " << qt_return << std::endl;

        SDL sdl(SDL_INIT_VIDEO);
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);
        auto Width = 1544;
        auto Height = 600;
        SDL2pp::Window sdlWindow("RocketLeague", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                 Width, Height,SDL_WINDOW_RESIZABLE);
        SDL_SetWindowResizable(sdlWindow.Get(), SDL_FALSE);

        // Creo renderer
        Renderer renderer(sdlWindow, -1, SDL_RENDERER_SOFTWARE);
        Texture car(renderer,SDL2pp::Surface("../images/car.jpeg").SetColorKey(true, 0));
        Texture ball(renderer,SDL2pp::Surface("../images/ball.png").SetColorKey(true, 0));
        Texture field(renderer,SDL2pp::Surface("../images/field.png").SetColorKey(true, 0));
        Texture scoreBoard(renderer,SDL2pp::Surface("../images/clock.png"));

        textures.emplace("car", &car);
        textures.emplace("ball", &ball);
        textures.emplace("field", &field);
        textures.emplace("scoreBoard", &scoreBoard);

        std::map<uint8_t, GameSprite> sprites;
        std::cout << "RenderThread: Iniciando loop principal" << std::endl;
        ClientUpdate* update;
        while (!updatesQueue.tryPop(update) and update) {
            Ball bola = dynamic_cast<ClientUpdateWorld *>(update)->getBall();
            std::cout << "Ball: " << (int) bola.getX() << " " << (int) bola.getY() << std::endl;
            Score score = dynamic_cast<ClientUpdateWorld *>(update)->getScore();
            std::cout << "Score: " << (int) score.getLocal() << " " << (int) score.getVisitor() << std::endl;

            std::vector<Car> players = dynamic_cast<ClientUpdateWorld *>(update)->getCars();
            for (auto &player: players) {
                std::cout << "Player: " << (int) player.getX() << " " << (int) player.getY() << std::endl;
            }
            delete update;
        }


        SDL_Event event;
        bool quit = false;
        while(!quit) {
            SDL_WaitEvent(&event);

            switch (event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
            SDL_RenderCopy(renderer.Get(), field.Get(), NULL, NULL);
            SDL_RenderPresent(renderer.Get());
        }
//        Worldview worldview(textures, sprites);
//
//        GameLoop gameLoop(mainWindow.id, renderer, Width, Height, updatesQueue, actionsQueue, worldview);
//        gameLoop.run();

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en la función main" << std::endl;
    }
}

//  Closes the accepting socket and forces all the client managers to finish
void RenderThread::stop() {
    join();
}

RenderThread::~RenderThread() {
    join();
}

// Copyright 2022 Sprenger Roberta

#include <QApplication>
#include "RenderThread.h"
#include "sub_client/client_sdl/Worldview.h"
using namespace SDL2pp;

RenderThread::RenderThread(const char *host, const char *port) : skt_client(host, port){}

void RenderThread::run() {
    uint8_t id = 0;
    BlockingQueue<std::shared_ptr<ClientAction>> actionsQueue;
    ProtectedQueue<std::shared_ptr<ClientUpdate>> updatesQueue;

    ThreadActionsSender sender(skt_client, actionsQueue);
    UpdatesReceiverThread receiver(skt_client, updatesQueue);

    sender.start();
    receiver.start();
    try {
        // Clase que contiene el loop principal
        int argc = 0;
        QApplication app(argc, nullptr);
        // Instancio la ventana principal
        MainWindow mainWindow(id, nullptr, updatesQueue, actionsQueue);
        mainWindow.show();
        mainWindow.displayMainMenu();

        // exec es una función bloqueante, cuando QT finaliza su ejecución, se realiza un return con el codigo de error
        int qt_return = app.exec();
        if (qt_return) {
            throw std::runtime_error("La aplicación QT finalizó de forma incorrecta");
        }
        // Initialize SDL library
        std::cout << "QT finalizó correctamente con: " << qt_return << std::endl;
        std::cout <<"id: " << (int)id << std::endl;
        std::shared_ptr<ClientUpdate> update; //startedGameACK
        bool popping = true;
        while (popping) {
            //  wait for updates
            if(updatesQueue.tryPop(update) and update) {
                if(!update->getReturnCode()) {
                    popping = false;
                }
            }
        }

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
//        GameLoop gameLoop(renderer, Width, Height, updatesQueue, actionsQueue, worldview);
//        gameLoop.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en la función main" << std::endl;
    }
    sender.join();
    receiver.join();
}

//  Closes the accepting socket and forces all the client managers to finish
void RenderThread::stop() {
    join();
}

RenderThread::~RenderThread() {
    join();
}

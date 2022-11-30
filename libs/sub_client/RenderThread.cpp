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
        // Creo renderer
        Renderer renderer(sdlWindow, -1, SDL_RENDERER_SOFTWARE);
        Texture carTexture(renderer, SDL2pp::Surface("../images/car.jpeg").SetColorKey(true, 0));
        Texture ballTexture(renderer, SDL2pp::Surface("../images/ball.png").SetColorKey(true, 0));
        Texture fieldTexture(renderer, SDL2pp::Surface("../images/field.png").SetColorKey(true, 0));
        Texture scoreBoardTexture(renderer, SDL2pp::Surface("../images/clock.png"));

        textures.emplace("car", &carTexture);
        textures.emplace("ball", &ballTexture);
        textures.emplace("field", &fieldTexture);
        textures.emplace("scoreBoard", &scoreBoardTexture);
        std::map<uint8_t, GameSprite> sprites;

        Ball ball = update->getBall();
        std::cout << "Ball: " << (int)ball.getX() << " " << (int)ball.getY() << std::endl;
        Score score = update->getScore();
        std::cout << "Score: " << (int)score.getLocal() << " " << (int)score.getVisitor() << std::endl;

        std::vector<Car> players = update->getCars();
        for (auto &player : players) {
            std::cout << "Player: " << (int)player.getX() << " " << (int)player.getY() << std::endl;
        }

        sprites.emplace(BALL, GameSprite(textures["ballTexture"], 0,Width/2,Height/3, 0));
        sprites.emplace(SCORE, GameSprite(textures["scoreBoard"],SCORE, Width/2, 0, 0));
        for (auto &player : players) {
            sprites.emplace(player.getId(), GameSprite(textures["carTexture"], player.getId(), player.getX(), player.getY(), player.getAngle()));
        }

        Worldview worldview(textures, sprites);
        GameLoop gameLoop(renderer, Width, Height, updatesQueue, actionsQueue, worldview);
        gameLoop.run();
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

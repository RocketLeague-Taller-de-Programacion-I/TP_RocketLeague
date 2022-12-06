// Copyright 2022 Sprenger Roberta

#include <QApplication>
#include "GameRenderer.h"
#include "sub_client/client_sdl/Worldview.h"

#define MUSIC_VOLUME 0
using namespace SDL2pp;

GameRenderer::GameRenderer(const char *host, const char *port) : skt_client(host, port){}

void GameRenderer::run() {
    uint8_t id = 0;
    BlockingQueue<std::optional<std::shared_ptr<ClientAction>>> actionsQueue;
    ProtectedQueue<std::shared_ptr<ClientUpdate>> updatesQueue;

    sender = new ActionsSenderThread(skt_client, actionsQueue);
    receiver = new UpdatesReceiverThread(skt_client, updatesQueue);

    startThreads();

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
        std::cout << "QT finalizó correctamente con: " << qt_return << std::endl;

        // Initialize SDL library
        SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
        //inizialize ttf library
        SDLTTF ttf;
        //initialize sdl mixer library
        Mixer mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

        //The music that will be played
        Music *music = nullptr;
        music = new Music("../assets/sounds/backgroundMusic.mp3");
        mixer.SetMusicVolume(MUSIC_VOLUME);
        mixer.FadeInMusic(*music);
        // Open a window
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);
        auto Width = 1544;
        auto Height = 600;
        SDL2pp::Window sdlWindow("RocketLeague", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                 Width, Height,SDL_WINDOW_RESIZABLE);
        SDL_SetWindowResizable(sdlWindow.Get(), SDL_FALSE);
        // Creo renderer
        Renderer renderer(sdlWindow, -1, SDL_RENDERER_SOFTWARE);

        //textures
        Texture blueCarTexture(renderer, SDL2pp::Surface("../assets/images/blueCar.png").SetColorKey(true, 0));
        Texture redCarTexture(renderer, SDL2pp::Surface("../assets/images/redCar.png").SetColorKey(true, 0));
        Texture ballTexture(renderer, SDL2pp::Surface("../assets/images/ball.png").SetColorKey(true, 0));
        Texture fieldTexture(renderer, SDL2pp::Surface("../assets/images/field.png").SetColorKey(true, 0));

        //setting tfont for score
        int fontsize = 50;
        Color color(0, 0, 0);
//        Color color(255,255, 255);
        std::string fontpath = "../assets/fonts/Jost-500-Medium.ttf";
        std::string text = "0 1 2 3 4 5 6 7 8 9 - Local Visitor : ";
        Font font(fontpath.c_str(), fontsize);
        Surface text_surface = font.RenderText_Solid(text, color);
        // create a texture from the surface
        Texture scoreTexture(renderer,text_surface);

        textures.emplace("redCarTexture", &redCarTexture);
        textures.emplace("blueCarTexture", &blueCarTexture);
        textures.emplace("ballTexture", &ballTexture);
        textures.emplace("fieldTexture", &fieldTexture);
        textures.emplace("scoreTexture", &scoreTexture);

        Worldview worldview(textures, Width, Height);
        GameLoop gameLoop(id, renderer, Width, Height, updatesQueue, actionsQueue, worldview);
        gameLoop.run();

        //free everything
        mixer.HaltMusic();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en la función main" << std::endl;
    }
    stop();
}

void GameRenderer::cleanThreads() {
    sender->stop();
    receiver->stop();

    sender->join();
    receiver->join();

    delete sender;
    delete receiver;
}

//  Closes the accepting socket and forces all the client managers to finish
void GameRenderer::stop() {
    skt_client.shutdown(2);
    skt_client.close();
    cleanThreads();
}

void GameRenderer::startThreads() {
    sender->start();
    receiver->start();
}

GameRenderer::~GameRenderer() {}

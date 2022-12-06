#include <QApplication>
#include "GameRenderer.h"
#include "sub_client/client_sdl/Worldview.h"

#define MUSIC_VOLUME 0
using namespace SDL2pp;

GameRenderer::GameRenderer(const char *host, const char *port) : skt_client(host, port){}

void GameRenderer::run() {
    uint8_t id = 0;
    while(!quit) {

        BlockingQueue<std::optional<std::shared_ptr<ClientAction>>> actionsQueue;
        ProtectedQueue<std::shared_ptr<ClientUpdate>> updatesQueue;

        sender = new ActionsSenderThread(skt_client, actionsQueue);
        receiver = new UpdatesReceiverThread(skt_client, updatesQueue);

        startThreads();

        try {
            // QT - Main Window
            int argc = 0;
            QApplication app(argc, nullptr);

            MainWindow mainWindow(id, nullptr, updatesQueue, actionsQueue);
            mainWindow.show();
            mainWindow.displayMainMenu();

            int qt_return = app.exec();
            if (qt_return) {
                quit = true;
                throw std::runtime_error("La aplicación QT finalizó de forma incorrecta");
            }
            std::cout << "QT finalizó correctamente con: " << qt_return << std::endl;

            if (id == 0) {
                //the user quited QT before the game started
                quit = true;
                break;
            }
            // SDL - Render
            // Initialize SDL library
            SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
            SDLTTF ttf;
            Mixer mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

            //The music that will be played
            Music *music = NULL;
            music = new Music("../assets/sounds/backgroundMusic.mp3");
            mixer.SetMusicVolume(MUSIC_VOLUME);
            mixer.FadeInMusic(*music);

            // Open a window
            SDL_DisplayMode DM;
            SDL_GetCurrentDisplayMode(0, &DM);
            auto Width = 1544;
            auto Height = 600;
            SDL2pp::Window sdlWindow("RocketLeague", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                     Width, Height, SDL_WINDOW_RESIZABLE);
            Renderer renderer(sdlWindow, -1, SDL_RENDERER_SOFTWARE);

            //textures
            Texture blueCarTexture(renderer, SDL2pp::Surface("../assets/images/blueCar.png").SetColorKey(true, 0));
            Texture redCarTexture(renderer, SDL2pp::Surface("../assets/images/redCar.png").SetColorKey(true, 0));
            Texture ballTexture(renderer, SDL2pp::Surface("../assets/images/ball.png").SetColorKey(true, 0));
            Texture fieldTexture(renderer, SDL2pp::Surface("../assets/images/field.png").SetColorKey(true, 0));
            Texture scoreBoard(renderer, SDL2pp::Surface("../assets/images/scoreBoard.png").SetColorKey(false, 0));

            int fontsize = 50;
            Color color(0, 0, 0);
            std::string fontpath = "../assets/fonts/Jost-500-Medium.ttf";
            std::string text = "0 1 2 3 4 5 6 7 8 9 - Local Visitor : ";
            Font font(fontpath.c_str(), fontsize);
            Surface text_surface = font.RenderText_Solid(text, color);
            Texture scoreTexture(renderer, text_surface);

            textures.emplace("redCarTexture", &redCarTexture);
            textures.emplace("blueCarTexture", &blueCarTexture);
            textures.emplace("ballTexture", &ballTexture);
            textures.emplace("fieldTexture", &fieldTexture);
            textures.emplace("scoreTexture", &scoreTexture);
            textures.emplace("scoreBoardTexture", &scoreBoard);

            Worldview worldview(textures, Width, Height);
            GameLoop gameLoop(id, renderer, Width, Height, updatesQueue, actionsQueue, worldview);
            quit = gameLoop.run();

            //free everything
            mixer.HaltMusic();
            // reset the id
            id = 0;
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Error desconocido en la función main" << std::endl;
        }
        stop();
    }
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

//cannot use because of RAII
void GameRenderer::loadTextures(Renderer &renderer) {
    //textures
    Texture blueCarTexture(renderer, SDL2pp::Surface("../assets/images/blueCar.png").SetColorKey(true, 0));
    Texture redCarTexture(renderer, SDL2pp::Surface("../assets/images/redCar.png").SetColorKey(true, 0));
    Texture ballTexture(renderer, SDL2pp::Surface("../assets/images/ball.png").SetColorKey(true, 0));
    Texture fieldTexture(renderer, SDL2pp::Surface("../assets/images/field.png").SetColorKey(true, 0));
    Texture scoreBoard(renderer, SDL2pp::Surface("../assets/images/scoreBoard.png").SetColorKey(true, 0));

    //setting tfont for score
    int fontsize = 50;
    Color color(0, 0, 0);
    //        Color color(255,255, 255);
    std::string fontpath = "../assets/fonts/Jost-500-Medium.ttf";
    std::string text = "0 1 2 3 4 5 6 7 8 9 - Local Visitor : ";
    Font font(fontpath.c_str(), fontsize);
    Surface text_surface = font.RenderText_Solid(text, color);
    // create a texture from the surface
    Texture scoreTexture(renderer, text_surface);

    textures.emplace("redCarTexture", &redCarTexture);
    textures.emplace("blueCarTexture", &blueCarTexture);
    textures.emplace("ballTexture", &ballTexture);
    textures.emplace("fieldTexture", &fieldTexture);
    textures.emplace("scoreTexture", &scoreTexture);
    textures.emplace("scoreBoardTexture", &scoreBoard);
}

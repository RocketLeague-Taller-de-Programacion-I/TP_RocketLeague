// Copyright 2022 Sprenger Roberta

#include <QApplication>
#include "RenderThread.h"
#include "Worldview.h"
#include "sub_common/sub_action/ActionUpdate.h"

using namespace SDL2pp;

RenderThread::RenderThread(ProtectedQueue<Action *> &updates, BlockingQueue<Action *> &actionsQueue)
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

        SDL sdl(SDL_INIT_VIDEO);
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);
        auto Width = DM.w;
        auto Height = DM.h;
        SDL2pp::Window sdlWindow("RocketLeague", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                 Width, Height,
                                 SDL_WINDOW_RESIZABLE);

        // Creo renderer
        Renderer renderer(sdlWindow, -1, SDL_RENDERER_SOFTWARE);
        Texture car(renderer,
                           SDL2pp::Surface("../images/car.jpeg").SetColorKey(true, 0));
        Texture ball(renderer,
                            SDL2pp::Surface("../images/ball.png").SetColorKey(true, 0));
//        Texture background(renderer,
//                                  SDL2pp::Surface("../images/background.jpeg").SetColorKey(true, 0));
        Texture scoreBoard(renderer,SDL2pp::Surface("../images/clock.png"));
        textures.emplace("car", &car);
        textures.emplace("ball", &ball);
//        textures.emplace("background", &background);
        textures.emplace("scoreBoard", &scoreBoard);
        SDL_SetTextureBlendMode(ball.Get(), SDL_BLENDMODE_BLEND);
        SDL_RenderCopy(renderer.Get(), ball.Get(), NULL, NULL);
        // map of Sprite
        std::map<uint8_t, GameSprite> sprites;
        //pop everything from updates queue
        //vector of Action*
        std::vector<Action *> actions;
//        std::vector<ActionUpdate*> actions;
        std::string name = "car1";
        uint8_t id = 1;
        actions.push_back(new ActionUpdate(id,name));
        name = "car2";
        id = 2;
        actions.push_back(new ActionUpdate(id,name));
        name = "ball";
        id = 6;
        actions.push_back(new ActionUpdate(id,name));
        name = "scoreBoard";
        id = 7;
        actions.push_back(new ActionUpdate(id,name));

        updatesQueue.tryPop(actions[0]);

//        for(int i = 0; i < 1; i++){ //2 players 1 score 1 ball
//            updatesQueue.tryPop(actions[i]);
//             id of players (1,2,3,4)
//             id score (5)
//             id ball (6)
        ActionUpdate *actionUpdate = dynamic_cast<ActionUpdate *>(actions[0]);
//        for(auto &actionUpdate : actions) {
            if(actionUpdate->getGameName() == "car1") {
                sprites.emplace(actionUpdate->getId(), GameSprite(textures["car"], actionUpdate->getId(), 0, Height / 2, actionUpdate->getAngle()));
            } else if(actionUpdate->getGameName() == "car2") {
                sprites.emplace(actionUpdate->getId(), GameSprite(textures["car"], actionUpdate->getId(), Height / 2, 0, actionUpdate->getAngle()));
            } else if(actionUpdate->getGameName() == "ball") {
                sprites.emplace(actionUpdate->getId(), GameSprite(textures["ball"], actionUpdate->getId(), Width / 2, Height / 3, actionUpdate->getAngle()));
            } else if(actionUpdate->getGameName() == "scoreBoard") {
                sprites.emplace(SCORE, GameSprite(textures["scoreBoard"], actionUpdate->getId(), Width / 2, 0, 0));
            }

//            switch(actionUpdate->getId()) {
//                case CAR:
//                    sprites.emplace(actionUpdate->getIdCreatorGame(), GameSprite(textures["car"], actionUpdate->getId(), actionUpdate->getX(), actionUpdate->getY(), actionUpdate->getAngle()));
//                    break;
//                case BALL:
//                    sprites.emplace(BALL, GameSprite(textures["ball"],actionUpdate->getId(), actionUpdate->getX(), actionUpdate->getY(), actionUpdate->getAngle()));
//                    break;
//                case SCORE:
//                    sprites.emplace(SCORE, GameSprite(textures["scoreBoard"],actionUpdate->getId(), Width / 2, 0, 0));
//                    break;
//            }


        Worldview worldview(textures, sprites);

        GameLoop gameLoop(renderer, Width, Height, updatesQueue, actionsQueue, worldview);
        gameLoop.run();

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

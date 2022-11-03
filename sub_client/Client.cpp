//
// Created by franco on 24/10/22.
//

#include <iostream>
#include "Client.h"
#include "mainwindow.h"
#include <cmath>
#include <iostream>

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

int Client::view_screen() {
// Initialize SDL library
    SDL sdl(SDL_INIT_VIDEO);

    // Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
    Window window("Rocket League",
                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                  640, 320,
                  SDL_WINDOW_RESIZABLE);

    // Create accelerated video renderer with default driver
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load sprites image as a new texture
    Texture sprites(renderer, "../images/rocketLig.jpg");

    // Main loop
    while (1) {
        // Event processing:
        // - If window is closed, or Q or Escape buttons are pressed,
        //   quit the application
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return 0;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        return 0;
                }
            }
        }
        // Clear screen
        renderer.Clear();

        // Draw player sprite
        renderer.Copy(sprites);

        // Show rendered frame
        renderer.Present();
    }
}
int Client::qt_init(int argc, char *argv[]) {
    QApplication app(argc, argv);
    mainwindow window;
//    Greeter greeter;
//    greeter.setWindowState(greeter.windowState());
//    greeter.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    greeter.setStyleSheet("image: url(../images/rocketLig.jpg);" "background-repeat: no-repeat;" "background-position: center;");
//    greeter.show();
    window.show();
    return app.exec();
}
void Client::start() {
    qt_init(0, nullptr);
    //view_screen();
}

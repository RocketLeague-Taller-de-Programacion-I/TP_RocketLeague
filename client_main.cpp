#include <cmath>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDLImage.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Surface.hh>
#include <QLabel>
#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>

#include "sub_client/RenderThread.h"


using namespace SDL2pp;

int main(int argc, char* argv[]) try {
    RenderThread render_thread(argv[1], argv[2]);
    render_thread.start();
    render_thread.join();
} catch (std::exception & e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
}

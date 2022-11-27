/*
  libSDL2pp - C++ bindings/wrapper for SDL2
  Copyright (C) 2013-2015 Dmitry Marakasov <amdmi3@amdmi3.ru>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

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
#include "sub_client/Client.h"

using namespace SDL2pp;
#define TESTDATA_DIR "../libSDL2pp/testdata"
static const float pi = 3.14159265358979323846f;

int main(int argc, char* argv[]) try {
   Client client(argv[1], argv[2]);
   // Lanzan dos hilos de mas. Client podría ejecutarse en el hilo main (en donde renderizarían). Solamente lanzarían el hilo sender y el receiver. 
   // No creen hilos para esperarlos inmediatamente.  
   client.start();
   client.join();
} catch (std::exception & e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return 1;
}

// Copyright 2022 Sprenger Roberta

#ifndef ROCKETLEAGUE_GAMERENDERER_H
#define ROCKETLEAGUE_GAMERENDERER_H

#include <atomic>
#include <utility>
#include <vector>
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

#include "sub_common/socket.h"
#include "sub_common/liberror.h"

#include "sub_client/UpdatesReceiverThread.h"
#include "sub_client/ActionsSenderThread.h"

#include "sub_client/client_qt/mainwindow.h"

class GameRenderer {
private:
    Socket skt_client;
    ActionsSenderThread* sender;
    UpdatesReceiverThread* receiver;
protected:
    std::map<std::string,SDL2pp::Texture*> textures;
public:
    GameRenderer(const char *host, const char *port);
    ~GameRenderer();

    void run();
    void stop();

    void cleanThreads();
    void startThreads();

};

#endif  //  ROCKETLEAGUE_GAMERENDERER_H

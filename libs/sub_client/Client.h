//
// Created by franco on 24/10/22.
//

#ifndef ROCKETLEAGUE_SERVER_H
#define ROCKETLEAGUE_SERVER_H

#include <cmath>
#include <iostream>
#include <QApplication>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDLImage.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Surface.hh>
#include <SDL.h>

#include "RenderThread.h"
#include "../sub_common/socket.h"
#include "sub_common/ClientSender.h"

class Client {
private:
    Socket skt_client;
public:
    Client(const char *host, const char *port);
    ~Client();
    void start();
};


#endif //ROCKETLEAGUE_SERVER_H

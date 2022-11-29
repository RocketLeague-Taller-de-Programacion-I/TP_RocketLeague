// Copyright 2022 Sprenger Roberta

#ifndef ROCKETLEAGUE_RENDERTHREAD_H
#define ROCKETLEAGUE_RENDERTHREAD_H

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

#include "sub_common/thread.h"
#include "sub_common/socket.h"
#include "sub_common/liberror.h"

#include "sub_client/UpdatesReceiverThread.h"
#include "sub_client/ThreadActionsSender.h"

#include "sub_client/client_qt/mainwindow.h"

class RenderThread : public Thread {
private:
    Socket skt_client;

protected:
//    ProtectedQueue<std::shared_ptr<ClientUpdate>> updatesQueue;
//    BlockingQueue<std::shared_ptr<ClientAction>> actionsQueue;
    std::map<std::string,SDL2pp::Texture*> textures;
    void run() override;
public:
    void stop() override;
    explicit RenderThread();

    ~RenderThread() override;

    RenderThread(const char *host, const char *port);
};

#endif  //  ROCKETLEAGUE_RENDERTHREAD_H

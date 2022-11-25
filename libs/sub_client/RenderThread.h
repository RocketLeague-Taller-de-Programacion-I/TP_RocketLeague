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

#include "../sub_common/thread.h"
#include "sub_common/liberror.h"
#include "mainwindow.h"

class RenderThread : public Thread {
private:
protected:
    ProtectedQueue<ClientUpdate*> &updatesQueue;
    BlockingQueue<ClientAction*> &actionsQueue;
    std::map<std::string,SDL2pp::Texture*> textures;
    void run() override;
public:
    void stop() override;
    explicit RenderThread();
    ~RenderThread() override;

    RenderThread(ProtectedQueue<ClientUpdate*> &updates, BlockingQueue<ClientAction *> &actionsQueue);
};

#endif  //  ROCKETLEAGUE_RENDERTHREAD_H

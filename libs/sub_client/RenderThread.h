// Copyright 2022 Sprenger Roberta

#ifndef ROCKETLEAGUE_RENDERTHREAD_H
#define ROCKETLEAGUE_RENDERTHREAD_H

#include <atomic>
#include <utility>
#include <vector>

#include "../sub_common/thread.h"
#include "sub_common/liberror.h"
#include "GameLoop.h"
#include "mainwindow.h"
#include "sub_common/BlockingQueue.h"

class RenderThread : public Thread {
private:
protected:
    BlockingQueue<std::string> &updatesQueue;
    void run() override;
public:
    void stop() override;
    explicit RenderThread();
    ~RenderThread() override;

    RenderThread(BlockingQueue<std::string> &updates);
};

#endif  //  ROCKETLEAGUE_RENDERTHREAD_H

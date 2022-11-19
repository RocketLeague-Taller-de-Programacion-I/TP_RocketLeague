// Copyright 2022 Sprenger Roberta

#ifndef ROCKETLEAGUE_RENDERTHREAD_H
#define ROCKETLEAGUE_RENDERTHREAD_H

#include <atomic>
#include <utility>
#include <vector>

#include "../sub_common/thread.h"
#include "sub_common/liberror.h"
#include "mainwindow.h"

class RenderThread : public Thread {
private:
protected:
    BlockingQueue<Action*> &updatesQueue;
    BlockingQueue<Action*> &actionsQueue;

    void run() override;
public:
    void stop() override;
    explicit RenderThread();
    ~RenderThread() override;

    RenderThread(BlockingQueue<Action *> &updates, BlockingQueue<Action *> &actionsQueue);
};

#endif  //  ROCKETLEAGUE_RENDERTHREAD_H

//
// Created by lucaswaisten on 04/11/22.
//

#ifndef ROCKETLEAGUE_THREAD_H
#define ROCKETLEAGUE_THREAD_H


#include <pthread.h>
#include <iostream>
#include <atomic>

class Thread {
private:
    pthread_t t;
    static void *runExpecting(void *self);
protected:
    virtual void run() = 0;
    std::atomic<bool> running = true;
public:
    void start();
    void join();
    virtual void stop() = 0;

    virtual ~Thread();

    bool isRunning();
};

#endif //ROCKETLEAGUE_THREAD_H

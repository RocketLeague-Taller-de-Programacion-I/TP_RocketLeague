//
// Created by lucaswaisten on 04/11/22.
//

#ifndef ROCKETLEAGUE_THREAD_H
#define ROCKETLEAGUE_THREAD_H


#include <pthread.h>
#include <iostream>

class Thread {
private:
    pthread_t t;
    static void *runExpecting(void *self);
protected:
    virtual void run() = 0;
public:
    void start();
    void join();
    virtual void stop() = 0;
    virtual ~Thread();
};

#endif //ROCKETLEAGUE_THREAD_H

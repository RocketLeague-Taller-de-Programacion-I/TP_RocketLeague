
#ifndef ROCKETLEAGUE_THREAD_H
#define ROCKETLEAGUE_THREAD_H

#include <iostream>
#include <thread>

class Thread {
private:
    std::thread thread;
public:
    //  Elimino constructor por copia
    Thread(const Thread&) = delete;
    //  Elimino operator = (copia)
    Thread& operator=(Thread&& other) = delete;
    //  Elimino constructor por movimiento
    Thread(Thread&& other) = delete;
    Thread();
    void start();
    void join();
    virtual void run() = 0;
    virtual void stop() = 0;
    virtual ~Thread();
};

#endif
//ROCKETLEAGUE_THREAD_H

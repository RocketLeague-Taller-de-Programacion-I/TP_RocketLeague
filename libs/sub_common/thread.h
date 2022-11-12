//
// Created by lucaswaisten on 04/11/22.
//

#ifndef ROCKETLEAGUE_THREAD_H
#define ROCKETLEAGUE_THREAD_H


#include <thread>
#include <utility>

class Thread {
public:
    Thread();
    virtual ~Thread();
    void start();
    void join();
    virtual void run() = 0;
    Thread(const Thread &) = delete;
    Thread &operator=(const Thread &) = delete;
    Thread(Thread &&otroThread) noexcept;
    Thread &operator=(Thread &&otroThread);

private:
    std::thread thread;
};


#endif //ROCKETLEAGUE_THREAD_H

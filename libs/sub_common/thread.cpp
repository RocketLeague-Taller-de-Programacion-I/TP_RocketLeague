//
// Created by lucaswaisten on 04/11/22.
//

#include "thread.h"

Thread::Thread() = default;

Thread::~Thread() = default;

void Thread::start() {
    this->thread = std::thread(&Thread::run, this);
}

void Thread::join() {
    this->thread.join();
}

Thread::Thread(Thread &&otroThread) noexcept {
    this->thread = std::move(otroThread.thread);
}

Thread &Thread::operator=(Thread &&otroThread) {
    this->thread = std::move(otroThread.thread);
    return *this;
}
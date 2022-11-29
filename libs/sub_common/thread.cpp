// Copyright 2022 Sprenger Roberta

#include "./thread.h"

Thread::Thread() { }
Thread::~Thread() { }
void Thread::join() {
    thread.join();
}
void Thread::start() {
    try {
        thread = std::thread(&Thread::run, this);
    } catch (const std::exception &e) {
        std::cerr << "Exception caught in a thread: '"
                  << e.what() << "'" << std::endl;
    }
}

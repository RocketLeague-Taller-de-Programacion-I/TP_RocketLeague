//
// Created by lucaswaisten on 04/11/22.
//

#include "thread.h"

Thread::Thread() = default;
Thread::~Thread() = default;

void Thread::join() {
    thread.join();
}
void Thread::start() {
    thread = std::thread(&Thread::run, this);
}
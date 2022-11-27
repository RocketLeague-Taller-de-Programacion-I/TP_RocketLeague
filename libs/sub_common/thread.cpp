// Copyright 2022 Sprenger Roberta

#include "./thread.h"


// Prefieran usar la clase Thread de c++ de Eze, no la que esta implementada con las funciones a lo C. (std::thread)
void *Thread::runExpecting(void *self) {
    try {
        //  cppcheck-suppress cstyleCast
        ((Thread*) self)->run();
    } catch (const std::exception &e) {
        std::cerr << "Exception caught in a thread: '" << e.what() << "'" << std::endl;
    } catch (...) {
        std::cerr << "Unknown error caught in thread" << std::endl;
    }
    return nullptr;
}

void Thread::start() {
    pthread_create(&t, nullptr, &Thread::runExpecting, this);
}

void Thread::join() {
    pthread_join(t, nullptr);
}

bool Thread::isRunning() {
    return running;
}

Thread::~Thread() = default;

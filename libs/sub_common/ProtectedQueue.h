#ifndef ROCKETLEAGUE_PROTECTEDQUEUE_H
#define ROCKETLEAGUE_PROTECTEDQUEUE_H

#pragma once
#include <mutex>
#include <queue>
#include <condition_variable>
#include <shared_mutex>
#include "QueueIsEmptyException.h"


template<typename T>
class ProtectedQueue
{
public:
    T pop() {
        std::lock_guard<std::mutex> lock(mutex);
        if (queue.empty()) {
            throw QueueIsEmptyException("Empty Queue Exception");
        }
        T element = queue.front();
        queue.pop();
        return element;

    }
    void push(T &element) {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(element);
    }
    bool isEmpty() {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }
    // pop if not empty
    bool tryPop(T &element) {
        std::lock_guard<std::mutex> lock(mutex);
        if (queue.empty()) {
            return false;
        }
        element = queue.front();
        queue.pop();
        return true;
    }
    std::queue<T> popAll() {
        std::lock_guard<std::mutex> lock(mutex);
        std::queue<T> old;
        std::queue<T> elements = this->queue;
        elements.swap(old);
        return old;
    }

    ~ProtectedQueue()  = default;


private:
    std::queue<T> queue;
    std::mutex mutex;
};
#endif //ROCKETLEAGUE_PROTECTEDQUEUE_H

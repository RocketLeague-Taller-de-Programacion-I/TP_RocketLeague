#ifndef ROCKETLEAGUE_PROTECTEDQUEUEBOUNDED_H
#define ROCKETLEAGUE_PROTECTEDQUEUEBOUNDED_H


#pragma once
#include <mutex>
#include <queue>
#include <condition_variable>
#include <shared_mutex>
#include "QueueIsEmptyException.h"


template<typename T>
class ProtectedQueueBounded {
public:
    explicit ProtectedQueueBounded(int capacity) : capacity(capacity) {};

    T pop() {
        std::lock_guard<std::mutex> lock(mutex);
        if (queue.empty()) {
            throw QueueIsEmptyException("Empty Queue Exception");
        }
        T element = queue.front();
        queue.pop();
        return element;

    }
    T push(T &element) {
        std::lock_guard<std::mutex> lock(mutex);
        T firstElement = queue.front();
        if(queue.size() == capacity){
            queue.pop();
        }
        queue.push(element);
        return firstElement;
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

    ~ProtectedQueueBounded()  = default;


private:
    std::queue<T> queue;
    std::mutex mutex;
    int capacity;
};
#endif //ROCKETLEAGUE_PROTECTEDQUEUEBOUNDED_H

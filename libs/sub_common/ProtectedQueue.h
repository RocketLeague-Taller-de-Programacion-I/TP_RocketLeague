//
// Created by lucaswaisten on 13/11/22.
//

#ifndef ROCKETLEAGUE_PROTECTEDQUEUE_H
#define ROCKETLEAGUE_PROTECTEDQUEUE_H

#pragma once
#include <mutex>
#include <queue>
#include <condition_variable>
#include "QueueIsEmptyException.h"


template<typename T>
class ProtectedQueue
{
public:
    T pop() {
        std::unique_lock<std::mutex> lock(mutex);
        if (isEmpty()) {
            throw QueueIsEmptyException("Empty Queue Exception");
        }
        T element = queue.front();
        queue.pop();
        return element;
    }
    void push(T &element) {
        std::unique_lock<std::mutex> lock(mutex);
        queue.push(element);
    }
    bool isEmpty() {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }
    // pop if not empty
    bool tryPop(T &element) {
        std::unique_lock<std::mutex> lock(mutex);
        if (isEmpty()) {
            return false;
        }
        element = queue.front();
        queue.pop();
        return true;
    }
    std::vector<T> popAll() {
        std::unique_lock<std::mutex> lock(mutex);
        std::vector<T> elements;
        while(!isEmpty()) {
            T element = queue.front();
            queue.pop();
            elements.push_back(element);
        }
        return elements;
    }


    ~ProtectedQueue()  = default;


private:
    std::queue<T> queue;
    mutable std::mutex mutex;
};
#endif //ROCKETLEAGUE_PROTECTEDQUEUE_H

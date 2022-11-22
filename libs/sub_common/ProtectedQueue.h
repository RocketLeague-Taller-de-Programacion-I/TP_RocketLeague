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
#include "BlockingQueue.h"

template<typename T>
class ProtectedQueue : public BlockingQueue<T>
{
public:
    T pop() override {
        std::unique_lock<std::mutex> lock(mutex);
        if (isEmpty()) {
            throw QueueIsEmptyException("Empty Queue Exception");
        }
        T element = queue.front();
        queue.pop();
        return element;
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

    ~ProtectedQueue() override = default;
private:
    std::queue<T> queue;
    mutable std::mutex mutex;
    std::condition_variable signal;
};
#endif //ROCKETLEAGUE_PROTECTEDQUEUE_H

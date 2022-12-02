//
// Created by lucaswaisten on 12/11/22.
//

#ifndef ROCKETLEAGUE_BQUEUE_H
#define ROCKETLEAGUE_BQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class BlockingQueue
{
public:
    void push(T &element) {
        std::unique_lock<std::mutex> lock(mutex);
        queue.push(element);
        signal.notify_all();
    }

    virtual T pop() {
        std::unique_lock<std::mutex> lock(mutex);
        wait_not_empty(lock);
        T element = queue.front();
        queue.pop();
        return element;
    }

    void wait_not_empty(std::unique_lock<std::mutex> &lock) {
        signal.wait(lock,[this]{return !queue.empty();});
    }

    bool isEmpty() {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }
    std::queue<T> popAll() {
        std::lock_guard<std::mutex> lock(mutex);
        std::queue<T> old;
        std::queue<T> elements = this->queue;
        elements.swap(old);
        return old;
    }

    virtual ~BlockingQueue() = default;

protected:
    std::queue<T> queue;
    mutable std::mutex mutex;
    std::condition_variable signal;
};

#endif //ROCKETLEAGUE_BQUEUE_H

//
// Created by lucaswaisten on 13/11/22.
//

#ifndef ROCKETLEAGUE_PROTECTEDQUEUE_H
#define ROCKETLEAGUE_PROTECTEDQUEUE_H

#include <mutex>
#include <queue>
#include <condition_variable>

template<typename T>
class ProtectedQueue
{
public:
    void push(T &element) {
        std::unique_lock<std::mutex> lock(mutex);
        queue.push(element);
        signal.notify_all();
    }

    T pop(){
        std::unique_lock<std::mutex> lock(mutex);
        T element = queue.front();
        queue.pop();
        return element;
    }

    bool isEmpty() {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }

private:
    std::queue<T> queue;
    mutable std::mutex mutex;
    std::condition_variable signal;
};
#endif //ROCKETLEAGUE_PROTECTEDQUEUE_H

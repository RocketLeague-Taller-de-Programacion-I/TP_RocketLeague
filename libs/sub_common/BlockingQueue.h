//
// Created by lucaswaisten on 12/11/22.
//
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

    T pop() {
        std::unique_lock<std::mutex> lock(mutex);
        wait_not_empty(lock);
        T element = queue.front();
        queue.pop();
        return element;
    }

    void wait_not_empty(std::unique_lock<std::mutex> &lock) {
        while(queue.empty()) {
            signal.wait(lock);
        }
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
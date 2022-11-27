//
// Created by lucaswaisten on 12/11/22.
//

#ifndef ROCKETLEAGUE_BQUEUE_H
#define ROCKETLEAGUE_BQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>


/*
    Falta agregar un `bool closed` y un método para cerrar la cola. Este consiste en 
      1) tomar el lock
      2) setear este booleano
      3) notify all

    El push debe lanzar una excepción si la cola está closed. 

    A su vez, el pop debe lanzar una excepción si la cola esta vacia y cerrada. 
    De este modo los hilos Sender (tanto del server como del client) se van a enterar que deben dejar de hacer pop de la cola y finalizan su método run. 
*/

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
        while(queue.empty()) {
            signal.wait(lock);
        }
    }

    bool isEmpty() {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }
    std::vector<T> popAll() {
        /*
         * // cambiar el tipo de retorno
         * std::queue<T> old;
         * {
         *      std::unique_lock<std::mutex> scopedUnique(mutex);
         *      std::swap(old, this.queue);
         * }
         * return old;
         */

        std::unique_lock<std::mutex> lock(mutex);
        std::vector<T> elements;
        while(queue.empty()) {
            T element = queue.front();
            queue.pop();
            elements.push_back(element);
        }
        return elements;
    }

    virtual ~BlockingQueue() = default;

protected:
    std::queue<T> queue;
    mutable std::mutex mutex;
    std::condition_variable signal;
};

#endif //ROCKETLEAGUE_BQUEUE_H

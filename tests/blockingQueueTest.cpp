//
// Created by lucaswaisten on 14/11/22.
//
#include <catch2/catch_test_macros.hpp>
#include "sub_common/BlockingQueue.h"
#include "sub_common/thread.h"

class TessterQueue : public Thread {
private:
    BlockingQueue<char> &queue;
    bool &waiting;
public:
    TessterQueue(BlockingQueue<char> &pQueue,
                 bool &b) :
                 queue(pQueue),
                 waiting(b){}

    void run() override {
       queue.pop();
       waiting = true;
    }

};

TEST_CASE("create a empty blockingQueue",
          "[single-file]") {
    BlockingQueue<char> queue;

    REQUIRE(queue.isEmpty() == true);
}
TEST_CASE("pushed two elements, verified if the queue is empty and popped the pushed element before",
          "[single-file]") {
    BlockingQueue<char> queue;
    char element1 = 'a';
    char element2 = 'b';

    queue.push(element1);
    queue.push(element2);

    REQUIRE(queue.size() == 2);
    REQUIRE(queue.isEmpty() == false);

    queue.pop();
    REQUIRE(queue.size() == 1);
    queue.pop();
    REQUIRE(queue.size() == 0);
}

/*
 * Este test prueba si la cola esta bloqueada tratando de hacer pop
 * cuando la cola esta vacia.
 */
TEST_CASE("thread is blocked trying to pop",
          "[single-file]") {
    BlockingQueue<char> queue;
    bool waiting(false);
    TessterQueue tester(queue,waiting);

    tester.start();
    /*
     * Como todavia esta vacia la cola, waiting nunca sera true
     */
    REQUIRE(waiting == false);

    char element1 = 'a';
    queue.push(element1);

    REQUIRE(waiting == true);
}
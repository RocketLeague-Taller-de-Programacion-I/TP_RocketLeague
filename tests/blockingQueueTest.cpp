#include <catch2/catch_test_macros.hpp>
#include <atomic>
#include "sub_common/BlockingQueue.h"
#include "sub_common/thread.h"

class TessterQueue : public Thread {
private:
    BlockingQueue<char> &queue;
    std::atomic<bool> &waiting;
public:
    TessterQueue(BlockingQueue<char> &pQueue,
                 std::atomic<bool> &b) :
                 queue(pQueue),
                 waiting(b){}
    void run() override {
       queue.pop();
       waiting = true;
    }
    void stop() override {join();}


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

    REQUIRE(queue.isEmpty() == false);

    auto i = queue.pop();
    REQUIRE(i == element1);
    i = queue.pop();
    REQUIRE(i == element2);
}

/*
 * Este test prueba si la cola esta bloqueada tratando de hacer pop
 * cuando la cola esta vacia.
 */

TEST_CASE("thread is blocked trying to pop",
          "[single-file]") {
    BlockingQueue<char> queue;
    std::atomic<bool> waiting(false);
    TessterQueue tester(queue,waiting);
    tester.start();
    /*
     * Como todavia esta vacia la cola, waiting nunca sera true
     */
    REQUIRE(waiting == false);

    char element1 = 'a';
    queue.push(element1);
    tester.stop();
    REQUIRE(waiting == true);
}
// For testing run
// g++ -std=c++23 test/testQueue.cpp -o /tmp/testQueue && /tmp/testQueue

#include <string>

#include "../include/classes/queue.h"
#include "common.h"

namespace {

void test_is_empty_queue_behaves_correctly() {
    Queue<int> queue;

    expect(queue.is_empty(), "new queue should be empty");
    expect(queue.size() == 0, "new queue should have size 0");

    bool threwFront = false;
    try {
        (void)queue.front();
    } catch (const std::runtime_error&) {
        threwFront = true;
    }
    expect(threwFront, "front() on empty queue should throw");

    bool threwDequeue = false;
    try {
        queue.dequeue();
    } catch (const std::runtime_error&) {
        threwDequeue = true;
    }
    expect(threwDequeue, "dequeue() on empty queue should throw");
}

void test_fifo_enqueue_and_dequeue() {
    Queue<int> queue;

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    expect(!queue.is_empty(), "queue should not be empty after enqueue");
    expect(queue.size() == 3, "queue size should increase with each enqueue");
    expect(queue.front() == 10, "front() should return the oldest element");

    queue.dequeue();
    expect(queue.front() == 20, "dequeue() should remove the oldest value");
    expect(queue.size() == 2, "size should decrease after dequeue");

    queue.dequeue();
    expect(queue.front() == 30, "second dequeue() should reveal the next item");

    queue.dequeue();
    expect(queue.is_empty(), "queue should be empty after removing all items");
    expect(queue.size() == 0, "queue size should be 0 when empty");
}

void test_dequeue_all_clears_queue() {
    Queue<std::string> queue;

    queue.enqueue("alpha");
    queue.enqueue("beta");
    queue.enqueue("gamma");

    queue.dequeue_all();

    expect(queue.is_empty(), "dequeue_all() should clear the queue");
    expect(queue.size() == 0, "size should be 0 after dequeue_all()");
}

void test_queue_supports_other_types() {
    Queue<double> queue;

    queue.enqueue(1.5);
    queue.enqueue(2.5);

    expect(queue.front() == 1.5, "queue should support floating-point values");
    queue.dequeue();
    expect(queue.front() == 2.5, "queue should continue to work after dequeue");
}

} // namespace

int main() {
    try {
        test_is_empty_queue_behaves_correctly();
        test_fifo_enqueue_and_dequeue();
        test_dequeue_all_clears_queue();
        test_queue_supports_other_types();
        std::cout << "All Queue tests are passed." << std::endl;
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Queue test failed: " << ex.what() << std::endl;
        return 1;
    }
}
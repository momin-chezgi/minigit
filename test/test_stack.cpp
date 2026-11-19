// To run this test:
// g++ -std=c++23 test/test_stack.cpp -o /tmp/test_stack && /tmp/test_stack

#include "../include/classes/stack.h"
#include "common.h"

namespace {
void test_is_empty_stack_behaves_correctly() {
    Stack<int> stack;
    expect(stack.is_empty(), "new stack should be is_empty");
    expect(stack.size() == 0, "new stack should have size 0");

    bool threwTop = false;
    try {
        (void)stack.top();
    } catch (const std::runtime_error&) {
        threwTop = true;
    }
    expect(threwTop, "top() on is_empty stack should throw");

    bool threwPop = false;
    try {
        stack.pop();
    } catch (const std::runtime_error&) {
        threwPop = true;
    }
    expect(threwPop, "pop() on is_empty stack should throw");
}

void test_lifo_push_and_pop() {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    expect(!stack.is_empty(), "stack should not be is_empty after pushes");
    expect(stack.size() == 3, "stack size should match number of pushed elements");
    expect(stack.top() == 30, "top() should return the most recently pushed value");

    stack.pop();
    expect(stack.top() == 20, "pop() should remove the most recent item");
    expect(stack.size() == 2, "size should decrease after pop");

    stack.pop();
    expect(stack.top() == 10, "second pop() should reveal the next item");

    stack.pop();
    expect(stack.is_empty(), "stack should be is_empty after all values are popped");
    expect(stack.size() == 0, "size should be 0 after clearing the stack");
}

void test_pop_all_clears_stack() {
    Stack<std::string> stack;
    stack.push("alpha");
    stack.push("beta");
    stack.push("gamma");

    stack.popAll();

    expect(stack.is_empty(), "popAll() should clear the stack");
    expect(stack.size() == 0, "popAll() should leave size at 0");
}

void test_stack_supports_other_types() {
    Stack<double> stack;
    stack.push(1.5);
    stack.push(2.5);

    expect(stack.top() == 2.5, "stack should support floating-point values");
    stack.pop();
    expect(stack.top() == 1.5, "stack should continue to work after popping");
}

}  // namespace

int main() {
    try {
        test_is_empty_stack_behaves_correctly();
        test_lifo_push_and_pop();
        test_pop_all_clears_stack();
        test_stack_supports_other_types();
        std::cout << "All Stack tests passed." << std::endl;
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Stack test failed: " << ex.what() << std::endl;
        return 1;
    }
}

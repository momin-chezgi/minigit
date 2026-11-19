
// g++ -std=c++23 -Wall -Wextra -Wpedantic test/test_fehrest.cpp -o /tmp/test_fehrest && /tmp/test_fehrest
#include <stdexcept>
#include <string>

#include "../include/classes/fehrest.h"
#include "common.h"

namespace {

void test_size_and_indexing() {
    Fehrest<int> values(3);
    expect(values.size() == 3, "Fehrest size should match constructor size");

    values[0] = 10;
    values[1] = 20;
    values[2] = 30;

    expect(values[0] == 10, "non-const indexing should read written values");
    expect(values[1] == 20, "non-const indexing should read written values");
    expect(values[2] == 30, "non-const indexing should read written values");

    const Fehrest<int>& constValues = values;
    expect(constValues[1] == 20, "const indexing should read values");

    bool threw = false;
    try {
        (void)values[3];
    } catch (const std::out_of_range&) {
        threw = true;
    }
    expect(threw, "operator[] should throw out_of_range for an invalid index");
}

void test_randomize_range() {
    Fehrest<int> values(100);
    values.randomize();

    for (std::size_t i = 0; i < values.size(); ++i) {
        expect(values[i] >= 1 && values[i] <= 2000,
               "randomize should generate values from 1 through 2000");
    }
}

void test_clone_is_independent() {
    Fehrest<int> values(3);
    values[0] = 11;
    values[1] = 22;
    values[2] = 33;

    std::unique_ptr<int[]> copy = values.clone();
    copy[1] = 99;

    expect(values[1] == 22, "clone modification should not affect the original");
    expect(copy[1] == 99, "clone should contain a mutable copy");
}

void test_copy_and_move() {
    Fehrest<int> original(2);
    original[0] = 7;
    original[1] = 8;

    Fehrest<int> copied(original);
    copied[0] = 70;
    expect(original[0] == 7, "copy constructor should not alias the original");

    Fehrest<int> moved(std::move(original));
    expect(moved.size() == 2, "move constructor should preserve size");
    expect(moved[0] == 7, "move constructor should transfer values");
    expect(original.size() == 0, "moved-from Fehrest should be empty");
}

} // namespace

int main() {
    try {
        test_size_and_indexing();
        test_randomize_range();
        test_clone_is_independent();
        test_copy_and_move();
        std::cout << "All Fehrest tests passed." << std::endl;
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Fehrest test failed: " << ex.what() << std::endl;
        return 1;
    }
}

# Fehrest Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Implement the owned-array `Fehrest<T>` class and repair the sort test's compile errors.

**Architecture:** Keep `Fehrest<T>` header-only because it is a template, use `std::unique_ptr<T[]>` for owned storage, and use copy/move constructors plus a clone method for independent arrays.

**Tech Stack:** C++23, standard library, existing plain-assert test style.

## Global Constraints

- Allocation and randomization must use 1 through 2000 for random values.
- `size() const` must report the element count.
- `operator[]` must provide const and non-const access and throw `std::out_of_range` on invalid indexes.
- `clone()` must return an independent `std::unique_ptr<T[]>`.
- Preserve the existing sorting headers and do not implement unrelated sorting algorithms.

---

### Task 1: Add Failing Fehrest Tests

**Files:**
- Create: `test/test_fehrest.cpp`

**Interfaces:**
- Consumes: `Fehrest<T>` constructor, `size() const`, `operator[]`, `randomize()`, and `clone()`.
- Produces: executable test coverage for allocation, bounds, random values, cloning, copy, and move.

- [ ] **Step 1: Create the focused test**

```cpp
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
```

- [ ] **Step 2: Compile and verify the test fails before implementation**

Run:

```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic test/test_fehrest.cpp -o /tmp/test_fehrest
```

Expected: failure from missing `randomize()`/copy/move implementations or `make_unique<int[]>` type mismatch, proving the test is red.

### Task 2: Implement Fehrest

**Files:**
- Modify: `include/classes/fehrest.h`

**Interfaces:**
- Produces: the methods exercised by `test/test_fehrest.cpp`.

- [ ] **Step 1: Implement the complete owned-array template**

```cpp
#pragma once

#include <cstddef>
#include <memory>
#include <random>
#include <stdexcept>
#include <utility>

template <typename T>
class Fehrest {
private:
    std::size_t count = 0;
    std::unique_ptr<T[]> arr;

public:
    explicit Fehrest(std::size_t n = 0)
        : count(n), arr(std::make_unique<T[]>(n)) {}

    Fehrest(const Fehrest& other)
        : count(other.count), arr(std::make_unique<T[]>(other.count)) {
        for (std::size_t i = 0; i < count; ++i) {
            arr[i] = other.arr[i];
        }
    }

    Fehrest& operator=(const Fehrest& other) {
        if (this != &other) {
            Fehrest<T> copied(other);
            *this = std::move(copied);
        }
        return *this;
    }

    Fehrest(Fehrest&& other) noexcept
        : count(other.count), arr(std::move(other.arr)) {
        other.count = 0;
    }

    Fehrest& operator=(Fehrest&& other) noexcept {
        if (this != &other) {
            count = other.count;
            arr = std::move(other.arr);
            other.count = 0;
        }
        return *this;
    }

    ~Fehrest() = default;

    std::unique_ptr<T[]> clone() const {
        auto copy = std::make_unique<T[]>(count);
        for (std::size_t i = 0; i < count; ++i) {
            copy[i] = arr[i];
        }
        return copy;
    }

    void randomize() {
        std::random_device device;
        std::mt19937 generator(device());
        std::uniform_int_distribution<int> distribution(1, 2000);
        for (std::size_t i = 0; i < count; ++i) {
            arr[i] = static_cast<T>(distribution(generator));
        }
    }

    T& operator[](std::size_t index) {
        if (index >= count) {
            throw std::out_of_range("Fehrest index is out of range");
        }
        return arr[index];
    }

    const T& operator[](std::size_t index) const {
        if (index >= count) {
            throw std::out_of_range("Fehrest index is out of range");
        }
        return arr[index];
    }

    std::size_t size() const noexcept {
        return count;
    }
};
```

- [ ] **Step 2: Compile and run the Fehrest test**

Run:

```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic test/test_fehrest.cpp -o /tmp/test_fehrest && /tmp/test_fehrest
```

Expected: `All Fehrest tests passed.`

### Task 3: Repair Sort Test and Remove Source Stub

**Files:**
- Modify: `test/test_sort.cpp`
- Modify: `src/classes/fehrest.cpp`

**Interfaces:**
- Consumes: `Fehrest<int>`.
- Produces: a compilable sort test executable that exercises the class.

- [ ] **Step 1: Replace the sort test with a focused compile-and-behavior test**

```cpp
#include "../include/classes/fehrest.h"
#include "common.h"

#include <algorithm>

int main() {
    try {
        Fehrest<int> values(5);
        values[0] = 50;
        values[1] = 10;
        values[2] = 40;
        values[3] = 20;
        values[4] = 30;

        std::sort(&values[0], &values[0] + values.size());

        expect(values[0] == 10, "sort should place 10 first");
        expect(values[1] == 20, "sort should place 20 second");
        expect(values[2] == 30, "sort should place 30 third");
        expect(values[3] == 40, "sort should place 40 fourth");
        expect(values[4] == 50, "sort should place 50 last");

        std::cout << "All sort integration tests passed." << std::endl;
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Sort integration test failed: " << ex.what() << std::endl;
        return 1;
    }
}
```

- [ ] **Step 2: Empty the template-only source file**

Replace `src/classes/fehrest.cpp` with:

```cpp
#include "../include/classes/fehrest.h"
```

- [ ] **Step 3: Compile and run all targeted tests**

Run:

```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic test/test_fehrest.cpp -o /tmp/test_fehrest && /tmp/test_fehrest
g++ -std=c++23 -Wall -Wextra -Wpedantic test/test_sort.cpp -o /tmp/test_sort && /tmp/test_sort
g++ -std=c++23 -Wall -Wextra -Wpedantic test/test_stack.cpp -o /tmp/test_stack && /tmp/test_stack
g++ -std=c++23 -Wall -Wextra -Wpedantic test/test_queue.cpp -o /tmp/test_queue && /tmp/test_queue
```

Expected: every executable prints `All ... tests passed.`

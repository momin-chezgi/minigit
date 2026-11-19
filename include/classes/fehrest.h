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
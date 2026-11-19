
#pragma once

#include <cstddef>
#include <iterator>
#include <utility>

// Sorts [first, last) in ascending order. Requires random-access iterators.
template <typename RandomIt>
void insertion_sort(RandomIt first, RandomIt last) {
    for (RandomIt current = first; current != last; ++current) {
        if (current == first) continue;
        auto value = std::move(*current);
        RandomIt position = current;
        while (position != first && value < *(position - 1)) {
            *position = std::move(*(position - 1));
            --position;
        }
        *position = std::move(value);
    }
}

// Sorts [A, A + n) in ascending order.
template <typename T>
void insertion_sort(T A[], std::size_t n) {
    if (n == 0) return;
    insertion_sort(A, A + n);
}

template <typename T, std::size_t N>
void insertion_sort(T (&A)[N]) {
    insertion_sort(A, N);
}


#pragma once

#include <cstddef>
#include <utility>

// Sorts [first, last) in ascending order. Requires writable iterators.
template <typename Iterator>
void selection_sort(Iterator first, Iterator last) {
    for (Iterator current = first; current != last; ++current) {
        Iterator smallest = current;
        Iterator candidate = current;
        for (++candidate; candidate != last; ++candidate) {
            if (*candidate < *smallest) {
                smallest = candidate;
            }
        }
        if (smallest != current) {
            using std::swap;
            swap(*current, *smallest);
        }
    }
}

template <typename T>
void selection_sort(T A[], std::size_t n) {
    if (n == 0) return;
    selection_sort(A, A + n);
}

template <typename T, std::size_t N>
void selection_sort(T (&A)[N]) {
    selection_sort(A, N);
}

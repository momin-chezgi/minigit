
#pragma once

#include <cstddef>
#include <iterator>
#include <utility>

namespace quick_sort_detail {
template <typename RandomIt>
void sort(RandomIt first, RandomIt last) {
    if (last - first < 2) return;

    // Use the last value as the pivot and move smaller values before it.
    const auto pivot = *(last - 1);
    RandomIt middle = first;
    for (RandomIt current = first; current != last - 1; ++current) {
        if (*current < pivot) {
            using std::swap;
            swap(*middle, *current);
            ++middle;
        }
    }

    using std::swap;
    swap(*middle, *(last - 1));

    // The pivot is now in its final position.
    sort(first, middle);
    sort(middle + 1, last);
}
}  // namespace quick_sort_detail

// Sorts [first, last) in ascending order. Requires random-access iterators.
template <typename RandomIt>
void quick_sort(RandomIt first, RandomIt last) {
    quick_sort_detail::sort(first, last);
}

template <typename T>
void quick_sort(T A[], std::size_t n) {
    if (n == 0) return;
    quick_sort(A, A + n);
}

template <typename T, std::size_t N>
void quick_sort(T (&A)[N]) {
    quick_sort(A, N);
}

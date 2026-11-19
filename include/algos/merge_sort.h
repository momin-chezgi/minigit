
#pragma once

#include <cstddef>
#include <iterator>
#include <vector>

namespace merge_sort_detail {
template <typename RandomIt, typename T>
void sort(RandomIt values, T* buffer, std::size_t first, std::size_t last) {
    if (last - first < 2) return;

    // Sort both halves, then merge them into the temporary buffer.
    const std::size_t middle = first + (last - first) / 2;
    sort(values, buffer, first, middle);
    sort(values, buffer, middle, last);

    std::size_t left = first;
    std::size_t right = middle;
    for (std::size_t out = first; out < last; ++out) {
        if (left < middle &&
            (right == last || !(values[right] < values[left]))) {
            buffer[out] = values[left++];
        } else {
            buffer[out] = values[right++];
        }
    }
    // Copy the merged values back into the input range.
    for (std::size_t i = first; i < last; ++i) {
        values[i] = buffer[i];
    }
}
}  // namespace merge_sort_detail

// Sorts [first, last) by sorting each half, then merging them together.
// Requires random-access iterators.
template <typename RandomIt>
void merge_sort(RandomIt first, RandomIt last) {
    using T = typename std::iterator_traits<RandomIt>::value_type;
    if (first == last) return;
    const auto length = last - first;
    const std::size_t n = static_cast<std::size_t>(length);
    if (n < 2) {
        return;
    }

    std::vector<T> buffer(n);
    merge_sort_detail::sort(first, buffer.data(), 0, n);
}

template <typename T>
void merge_sort(T A[], std::size_t n) {
    if (n == 0) return;
    merge_sort(A, A + n);
}

template <typename T, std::size_t N>
void merge_sort(T (&A)[N]) {
    merge_sort(A, N);
}

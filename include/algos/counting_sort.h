

#pragma once

#include <cstddef>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <vector>

// Sorts integral values by counting how often each value appears.
// Requires random-access iterators and a range of values small enough to count.
template <typename RandomIt>
void counting_sort(RandomIt first, RandomIt last) {
    using T = typename std::iterator_traits<RandomIt>::value_type;
    static_assert(std::is_integral_v<T> && !std::is_same_v<T, bool>,
                  "counting_sort requires a non-bool integral type");
    if (first == last) return;
    const auto length = last - first;
    const std::size_t n = static_cast<std::size_t>(length);
    if (n < 2) {
        return;
    }

    T minimum = first[0];
    T maximum = first[0];
    for (std::size_t i = 1; i < n; ++i) {
        if (first[i] < minimum) minimum = first[i];
        if (maximum < first[i]) maximum = first[i];
    }

    using Unsigned = std::make_unsigned_t<T>;
    // Unsigned subtraction gives the distance from minimum, even for negatives.
    const Unsigned range_minus_one = static_cast<Unsigned>(maximum) -
                                     static_cast<Unsigned>(minimum);
    if constexpr (std::numeric_limits<Unsigned>::digits >=
                  std::numeric_limits<std::size_t>::digits) {
        if (range_minus_one >= static_cast<Unsigned>(
                                  std::numeric_limits<std::size_t>::max())) {
            throw std::length_error("counting_sort value range is too large");
        }
    }
    // Stop if the distance cannot fit in a vector's index range.
    const std::size_t range = static_cast<std::size_t>(range_minus_one) + 1;
    std::vector<std::size_t> counts(range, 0);
    for (std::size_t i = 0; i < n; ++i) {
        const auto offset = static_cast<Unsigned>(first[i]) -
                            static_cast<Unsigned>(minimum);
        ++counts[static_cast<std::size_t>(offset)];
    }

    // Write each value back in increasing order, using its count.
    std::size_t output = 0;
    for (std::size_t offset = 0; offset < range; ++offset) {
        while (counts[offset] != 0) {
            first[output++] = static_cast<T>(static_cast<Unsigned>(minimum) +
                                             static_cast<Unsigned>(offset));
            --counts[offset];
        }
    }
}

template <typename T>
void counting_sort(T A[], std::size_t n) {
    if (n == 0) return;
    counting_sort(A, A + n);
}

template <typename T, std::size_t N>
void counting_sort(T (&A)[N]) {
    counting_sort(A, N);
}

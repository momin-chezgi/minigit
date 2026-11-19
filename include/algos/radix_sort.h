

#pragma once

#include <cstddef>
#include <iterator>
#include <limits>
#include <type_traits>
#include <vector>

// Sorts integers one byte at a time, starting with the least significant byte.
// Requires random-access iterators.
template <typename RandomIt>
void radix_sort(RandomIt first, RandomIt last) {
    using T = typename std::iterator_traits<RandomIt>::value_type;
    static_assert(std::is_integral_v<T> && !std::is_same_v<T, bool>,
                  "radix_sort requires a non-bool integral type");
    if (first == last) return;
    const auto length = last - first;
    const std::size_t n = static_cast<std::size_t>(length);
    if (n < 2) {
        return;
    }

    using Unsigned = std::make_unsigned_t<T>;
    constexpr unsigned bit_count = std::numeric_limits<Unsigned>::digits;
    constexpr unsigned byte_count = (bit_count + 7) / 8;
    // Flipping the sign bit makes signed integer keys sort in numeric order.
    constexpr Unsigned sign_mask = std::is_signed_v<T>
        ? (Unsigned{1} << (bit_count - 1)) : Unsigned{0};
    std::vector<T> buffer(n);

    for (unsigned byte = 0; byte < byte_count; ++byte) {
        // Count the current byte for every value.
        std::size_t counts[256] = {};
        const unsigned shift = byte * 8;
        for (std::size_t i = 0; i < n; ++i) {
            const Unsigned key = static_cast<Unsigned>(first[i]) ^ sign_mask;
            ++counts[static_cast<unsigned>((key >> shift) & Unsigned{0xff})];
        }

        // Convert counts into the starting position for each byte value.
        std::size_t offsets[256];
        std::size_t total = 0;
        for (std::size_t i = 0; i < 256; ++i) {
            offsets[i] = total;
            total += counts[i];
        }

        // Place values in order, then prepare for sorting the next byte.
        for (std::size_t i = 0; i < n; ++i) {
            const Unsigned key = static_cast<Unsigned>(first[i]) ^ sign_mask;
            const auto digit = static_cast<unsigned>((key >> shift) & Unsigned{0xff});
            buffer[offsets[digit]++] = first[i];
        }
        for (std::size_t i = 0; i < n; ++i) {
            first[i] = buffer[i];
        }
    }
}

template <typename T>
void radix_sort(T A[], std::size_t n) {
    if (n == 0) return;
    radix_sort(A, A + n);
}

template <typename T, std::size_t N>
void radix_sort(T (&A)[N]) {
    radix_sort(A, N);
}

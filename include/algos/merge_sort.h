
#include <cstddef>

namespace {
    template<typename T>
    void merge(T dst[], const T src[], std::size_t first,
               std::size_t middle, std::size_t last)
    {
        std::size_t i = first;
        std::size_t j = middle;

        for (std::size_t k = first; k < last; ++k) {
            if (i < middle && (j >= last || src[i] <= src[j])) {
                dst[k] = src[i++];
            } else {
                dst[k] = src[j++];
            }
        }
    }

    template<typename T>
    void merge_sort_impl(T dst[], T src[], std::size_t first,
                         std::size_t last)
    {
        if (last - first < 2) {
            return;
        }

        const std::size_t middle = (first + last) / 2;
        merge_sort_impl(src, dst, first, middle);
        merge_sort_impl(src, dst, middle, last);

        merge(dst, src, first, middle, last);
    }
}

template<typename T>
void merge_sort(T A[], std::size_t n)
{
    if (n < 2) {
        return;
    }

    T* buffer = new T[n];
    for (std::size_t i = 0; i < n; ++i) {
        buffer[i] = A[i];
    }

    merge_sort_impl(A, buffer, 0, n);
    delete[] buffer;
}

template<typename T, std::size_t N>
void merge_sort(T (&A)[N])
{
    merge_sort(A, N);
}
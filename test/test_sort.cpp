
#include <algorithm>
#include <random>
#include <iterator>
#include <functional>

#include "../include/algos/counting_sort.h"
#include "../include/algos/insertion_sort.h"
#include "../include/algos/merge_sort.h"
#include "../include/algos/quick_sort.h"
#include "../include/algos/radix_sort.h"
#include "../include/algos/selection_sort.h"
#include "../include/classes/fehrest.h"

namespace {
    Fehrest rf[]{
        Fehrest(1),Fehrest(2),Fehrest(10),Fehrest(20),Fehrest(30),Fehrest(40),Fehrest(50),Fehrest(100),Fehrest(1000)
    };
    template <typename T>
    std::function<void(T[], std::size_t)> funcs = {
        counting_sort,
        insertion_sort,
        merge_sort,
        quick_sort,
        radix_sort,
        selection_sort
    };
}

int main() {
    for (int i=0; i<std::size(ra);i++) {
        int n = ra[i].count;
        std::sort();
        int sorted[] = ra[i];
    }
}
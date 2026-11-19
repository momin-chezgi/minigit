#include "../include/classes/fehrest.h"
#include "common.h"

#include <algorithm>
#include <functional>

#include "../include/algos/counting_sort.h"
#include "../include/algos/insertion_sort.h"
#include "../include/algos/merge_sort.h"
#include "../include/algos/quick_sort.h"
#include "../include/algos/radix_sort.h"
#include "../include/algos/selection_sort.h"



namespace {
    const int testCount = 6;
    const int sortCount = 6;
    Fehrest<int> testingFeh[testCount] = {
        Fehrest<int>(1), Fehrest<int>(2), Fehrest<int>(5), Fehrest<int>(10), Fehrest<int>(100), Fehrest<int>(1000)
    };
    template<typename T>
    std::function<void(T[], std::size_t)> sort[sortCount] = {
        counting_sort<T>,
        insertion_sort<T>,
        merge_sort<T>,
        quick_sort<T>,
        radix_sort<T>,
        selection_sort<T>
    };
}

int main() {
    try {
        for (std::size_t i = 0; i<testCount; ++i){
            testingFeh[i].randomize();
        }
        for (std::size_t i = 0; i < testCount; ++i){
        for (std::size_t j = 0; j < sortCount; ++j){
            Fehrest<int> standard = testingFeh[i].clone();
            std::sort(standard.begin(), standard.end());

            Fehrest<int> newFeh = testingFeh[i].clone();
            std::function<void(int[], std::size_t)> sortingFunc = sort<int>[j];
            sortingFunc(newFeh, newFeh.size());
        }
    }


        std::cout << "All sort integration tests passed." << std::endl;
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Sort integration test failed: " << ex.what() << std::endl;
        return 1;
    }
}
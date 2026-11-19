#include "../include/classes/fehrest.h"
#include "common.h"

#include <algorithm>

int main() {
    try {
        Fehrest<int> values(5);
        values[0] = 50;
        values[1] = 10;
        values[2] = 40;
        values[3] = 20;
        values[4] = 30;

        std::sort(&values[0], &values[0] + values.size());

        expect(values[0] == 10, "sort should place 10 first");
        expect(values[1] == 20, "sort should place 20 second");
        expect(values[2] == 30, "sort should place 30 third");
        expect(values[3] == 40, "sort should place 40 fourth");
        expect(values[4] == 50, "sort should place 50 last");

        std::cout << "All sort integration tests passed." << std::endl;
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Sort integration test failed: " << ex.what() << std::endl;
        return 1;
    }
}
#pragma once

# include <string>
# include <stdexcept>
#include <iostream>


void expect(bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

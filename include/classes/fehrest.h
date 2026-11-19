#include <cstddef>
#include <memory>

// `Fehrest` is my special list that has specific features just in my work.
// This new class is because we can use std::vector, std::array or something like that 
template<typename T>
class Fehrest{
private:
    std::size_t count;
    std::unique_ptr<T[]> arr;  
public:
    Fehrest(std::size_t n) : count(n) {
        arr = std::make_unique<int[]>(count);
    }
    ~Fehrest(){};
    std::unique_ptr<T[]> clone();
    void randomize();
};
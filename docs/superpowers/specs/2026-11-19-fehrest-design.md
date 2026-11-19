# Fehrest Design

## Scope

Implement the existing `Fehrest<T>` template in `include/classes/fehrest.h` and
correct `test/test_sort.cpp` so it compiles and tests the class.

## API

- `Fehrest(std::size_t n)` allocates `n` elements of type `T`.
- `size() const` reports the element count.
- `operator[]` provides non-const and const indexed access.
- Index access throws `std::out_of_range` when the index is outside `[0, size())`.
- `randomize()` fills every element with a pseudo-random integral value from
  `1` through `2000`.
- `clone()` returns a new `T[]` allocation containing a copy of all elements.
- The class is move-capable and copy-capable. Copying allocates a new array;
  moving transfers ownership and leaves the moved-from object empty.

## Implementation

Because `Fehrest` is a template and the project has no separate template source
pattern, its methods will remain defined in the header. Storage will use
`std::unique_ptr<T[]>`; allocation and zero-length behavior will use
`std::make_unique<T[]>(n)`. Randomization will use a local
`std::random_device`, `std::mt19937`, and an integral distribution whose
result is converted to `T`.

## Tests

A focused Fehrest test will verify construction, bounds checking, randomization
range, cloning independence, const access, and copy/move behavior. The sort test
will use `Fehrest<int>` explicitly and avoid invalid function and array
conversions.

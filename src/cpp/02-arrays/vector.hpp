#pragma once

#include <cstddef>

namespace arrays {

// Dynamic array of ints backed by a raw heap-allocated buffer.
// Spec: README.md section 2.1.
//
// Contract the tests in vector_test.cpp assume (follow it exactly or the
// tests that aren't about a specific bug will fail for the wrong reason):
//
//   - a freshly constructed Vector has capacity() == 16 and size() == 0
//   - a write that would make size() exceed capacity() doubles capacity()
//     first (i.e. the check is "would this insert make size == capacity
//     before I had room?", so the 17th push on a 16-capacity vector grows
//     it to 32, not "grow only after overflowing")
//   - a removal that leaves size() == capacity() / 4 halves capacity(),
//     but capacity() never drops below the initial 16
//   - at(index), pop(), delete_at(index) throw std::out_of_range when
//     index/the vector is out of bounds (index >= size(), or empty for
//     pop())
//   - insert(index, item) throws std::out_of_range when index > size()
//     (index == size() is a valid append, same as prepend/push at the
//     ends)
//   - remove(item) deletes every element equal to item, shifting the rest
//     left; it's a no-op (no throw) if item isn't present
//   - find(item) returns the index of the first element equal to item, or
//     -1 if none match
//
// NOTE: `delete` is a reserved word in C++, so the spec's `delete(index)`
// is named delete_at(index) here.
//
// This header + vector.cpp are stubs: method bodies are intentionally
// empty (or return a placeholder) so vector_test.cpp compiles and fails,
// rather than erroring. Implement them yourself.
class Vector {
 public:
  Vector();
  ~Vector();

  Vector(const Vector&) = delete;
  Vector& operator=(const Vector&) = delete;

  std::size_t size() const;
  std::size_t capacity() const;
  bool is_empty() const;

  int at(std::size_t index) const;

  void push(int item);
  void insert(std::size_t index, int item);
  void prepend(int item);

  int pop();
  void delete_at(std::size_t index);
  void remove(int item);
  long find(int item) const;

 private:
  void resize(std::size_t new_capacity);

  int* data_;
  std::size_t size_;
  std::size_t capacity_;
};

}  // namespace arrays

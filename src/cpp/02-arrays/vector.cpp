#include "vector.hpp"

// Stub implementation only — see the contract in vector.hpp. Every method
// body below is intentionally empty (or returns a placeholder value) so
// that vector_test.cpp compiles and its assertions fail, instead of the
// build erroring or the tests segfaulting. Fill these in yourself.

namespace arrays {

Vector::Vector() : data_(nullptr), size_(0), capacity_(0) {
  // TODO: implement
}

Vector::~Vector() {
  // TODO: implement
}

std::size_t Vector::size() const {
  // TODO: implement
  return 0;
}

std::size_t Vector::capacity() const {
  // TODO: implement
  return 0;
}

bool Vector::is_empty() const {
  // TODO: implement
  return false;
}

int Vector::at(std::size_t index) const {
  // TODO: implement
  return 0;
}

void Vector::push(int item) {
  // TODO: implement
}

void Vector::insert(std::size_t index, int item) {
  // TODO: implement
}

void Vector::prepend(int item) {
  // TODO: implement
}

int Vector::pop() {
  // TODO: implement
  return 0;
}

void Vector::delete_at(std::size_t index) {
  // TODO: implement
}

void Vector::remove(int item) {
  // TODO: implement
}

long Vector::find(int item) const {
  // TODO: implement
  return -1;
}

void Vector::resize(std::size_t new_capacity) {
  // TODO: implement
}

}  // namespace arrays

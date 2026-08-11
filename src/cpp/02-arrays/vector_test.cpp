#include "vector.hpp"

#include <stdexcept>

#include <gtest/gtest.h>

namespace arrays {
namespace {

// Pushes 0, 1, ..., n-1 into v, in order. Takes v by reference (rather
// than building and returning a Vector by value) since Vector isn't
// copyable or movable.
void Fill(Vector& v, std::size_t n) {
  for (std::size_t i = 0; i < n; ++i) {
    v.push(static_cast<int>(i));
  }
}

// ---------------------------------------------------------------------------
// Construction
// ---------------------------------------------------------------------------

TEST(VectorConstruction, NewVectorIsEmpty) {
  Vector v;
  EXPECT_TRUE(v.is_empty());
}

TEST(VectorConstruction, NewVectorSizeIsZero) {
  Vector v;
  EXPECT_EQ(v.size(), 0u);
}

TEST(VectorConstruction, NewVectorCapacityIsSixteen) {
  Vector v;
  EXPECT_EQ(v.capacity(), 16u);
}

// ---------------------------------------------------------------------------
// is_empty
// ---------------------------------------------------------------------------

TEST(VectorIsEmpty, TrueWhenNoElements) {
  Vector v;
  EXPECT_TRUE(v.is_empty());
}

TEST(VectorIsEmpty, FalseAfterPush) {
  Vector v;
  v.push(1);
  EXPECT_FALSE(v.is_empty());
}

TEST(VectorIsEmpty, TrueAgainAfterPushThenPop) {
  Vector v;
  v.push(1);
  v.pop();
  EXPECT_TRUE(v.is_empty());
}

// ---------------------------------------------------------------------------
// size
// ---------------------------------------------------------------------------

TEST(VectorSize, IncreasesAfterPush) {
  Vector v;
  v.push(42);
  EXPECT_EQ(v.size(), 1u);
}

TEST(VectorSize, IncreasesAfterMultiplePush) {
  Vector v;
  Fill(v, 5);
  EXPECT_EQ(v.size(), 5u);
}

// ---------------------------------------------------------------------------
// at
// ---------------------------------------------------------------------------

TEST(VectorAt, ReturnsPushedValue) {
  Vector v;
  v.push(10);
  v.push(20);
  v.push(30);
  EXPECT_EQ(v.at(0), 10);
  EXPECT_EQ(v.at(1), 20);
  EXPECT_EQ(v.at(2), 30);
}

TEST(VectorAt, PreservesOrderAfterMultiplePush) {
  Vector v;
  Fill(v, 10);
  for (std::size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(v.at(i), static_cast<int>(i));
  }
}

TEST(VectorAt, OutOfRangeOnEmptyVectorThrows) {
  Vector v;
  EXPECT_THROW(v.at(0), std::out_of_range);
}

TEST(VectorAt, OutOfRangeWhenIndexEqualsSizeThrows) {
  Vector v;
  Fill(v, 3);
  EXPECT_THROW(v.at(3), std::out_of_range);
}

TEST(VectorAt, OutOfRangeWhenIndexBeyondSizeThrows) {
  Vector v;
  Fill(v, 3);
  EXPECT_THROW(v.at(100), std::out_of_range);
}

// ---------------------------------------------------------------------------
// push
// ---------------------------------------------------------------------------

TEST(VectorPush, AppendsToEnd) {
  Vector v;
  v.push(1);
  v.push(2);
  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(1), 2);
  EXPECT_EQ(v.size(), 2u);
}

TEST(VectorPush, SingleElement) {
  Vector v;
  v.push(99);
  EXPECT_EQ(v.size(), 1u);
  EXPECT_EQ(v.at(0), 99);
  EXPECT_FALSE(v.is_empty());
}

// ---------------------------------------------------------------------------
// insert
// ---------------------------------------------------------------------------

TEST(VectorInsert, AtBeginningShiftsElementsRight) {
  Vector v;
  Fill(v, 3);  // [0, 1, 2]
  v.insert(0, 99);
  EXPECT_EQ(v.size(), 4u);
  EXPECT_EQ(v.at(0), 99);
  EXPECT_EQ(v.at(1), 0);
  EXPECT_EQ(v.at(2), 1);
  EXPECT_EQ(v.at(3), 2);
}

TEST(VectorInsert, InMiddleShiftsTrailingElements) {
  Vector v;
  Fill(v, 4);  // [0, 1, 2, 3]
  v.insert(2, 99);
  EXPECT_EQ(v.size(), 5u);
  EXPECT_EQ(v.at(0), 0);
  EXPECT_EQ(v.at(1), 1);
  EXPECT_EQ(v.at(2), 99);
  EXPECT_EQ(v.at(3), 2);
  EXPECT_EQ(v.at(4), 3);
}

TEST(VectorInsert, AtEndBehavesLikePush) {
  Vector v;
  Fill(v, 3);  // [0, 1, 2]
  v.insert(3, 99);
  EXPECT_EQ(v.size(), 4u);
  EXPECT_EQ(v.at(3), 99);
}

TEST(VectorInsert, OutOfRangeThrows) {
  Vector v;
  Fill(v, 3);
  EXPECT_THROW(v.insert(4, 99), std::out_of_range);
}

TEST(VectorInsert, IntoEmptyVectorAtZero) {
  Vector v;
  v.insert(0, 5);
  EXPECT_EQ(v.size(), 1u);
  EXPECT_EQ(v.at(0), 5);
}

TEST(VectorInsert, CanTriggerGrowth) {
  Vector v;
  Fill(v, 16);  // capacity 16, full
  v.insert(0, 99);
  EXPECT_EQ(v.size(), 17u);
  EXPECT_EQ(v.capacity(), 32u);
}

// ---------------------------------------------------------------------------
// prepend
// ---------------------------------------------------------------------------

TEST(VectorPrepend, AddsToFront) {
  Vector v;
  Fill(v, 3);  // [0, 1, 2]
  v.prepend(99);
  EXPECT_EQ(v.size(), 4u);
  EXPECT_EQ(v.at(0), 99);
  EXPECT_EQ(v.at(1), 0);
  EXPECT_EQ(v.at(2), 1);
  EXPECT_EQ(v.at(3), 2);
}

TEST(VectorPrepend, OnEmptyVector) {
  Vector v;
  v.prepend(7);
  EXPECT_EQ(v.size(), 1u);
  EXPECT_EQ(v.at(0), 7);
}

TEST(VectorPrepend, MultipleMaintainsOrder) {
  Vector v;
  v.prepend(3);
  v.prepend(2);
  v.prepend(1);
  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(1), 2);
  EXPECT_EQ(v.at(2), 3);
}

// ---------------------------------------------------------------------------
// pop
// ---------------------------------------------------------------------------

TEST(VectorPop, RemovesLastElementAndReturnsIt) {
  Vector v;
  Fill(v, 3);  // [0, 1, 2]
  EXPECT_EQ(v.pop(), 2);
  EXPECT_EQ(v.size(), 2u);
}

TEST(VectorPop, DecreasesSize) {
  Vector v;
  Fill(v, 5);
  v.pop();
  EXPECT_EQ(v.size(), 4u);
}

TEST(VectorPop, OnEmptyVectorThrows) {
  Vector v;
  EXPECT_THROW(v.pop(), std::out_of_range);
}

TEST(VectorPop, SingleElementVectorBecomesEmpty) {
  Vector v;
  v.push(1);
  v.pop();
  EXPECT_TRUE(v.is_empty());
  EXPECT_EQ(v.size(), 0u);
}

// ---------------------------------------------------------------------------
// delete_at (spec: delete(index) — `delete` is a C++ keyword)
// ---------------------------------------------------------------------------

TEST(VectorDeleteAt, RemovesElementAndShiftsLeft) {
  Vector v;
  Fill(v, 4);  // [0, 1, 2, 3]
  v.delete_at(1);
  EXPECT_EQ(v.size(), 3u);
  EXPECT_EQ(v.at(0), 0);
  EXPECT_EQ(v.at(1), 2);
  EXPECT_EQ(v.at(2), 3);
}

TEST(VectorDeleteAt, FirstElement) {
  Vector v;
  Fill(v, 3);  // [0, 1, 2]
  v.delete_at(0);
  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(1), 2);
}

TEST(VectorDeleteAt, LastElement) {
  Vector v;
  Fill(v, 3);  // [0, 1, 2]
  v.delete_at(2);
  EXPECT_EQ(v.size(), 2u);
  EXPECT_EQ(v.at(0), 0);
  EXPECT_EQ(v.at(1), 1);
}

TEST(VectorDeleteAt, OutOfRangeThrows) {
  Vector v;
  Fill(v, 3);
  EXPECT_THROW(v.delete_at(3), std::out_of_range);
}

TEST(VectorDeleteAt, OnEmptyVectorThrows) {
  Vector v;
  EXPECT_THROW(v.delete_at(0), std::out_of_range);
}

// ---------------------------------------------------------------------------
// remove
// ---------------------------------------------------------------------------

TEST(VectorRemove, DeletesTheOnlyOccurrence) {
  Vector v;
  Fill(v, 3);  // [0, 1, 2]
  v.remove(1);
  EXPECT_EQ(v.size(), 2u);
  EXPECT_EQ(v.at(0), 0);
  EXPECT_EQ(v.at(1), 2);
}

TEST(VectorRemove, NonExistentValueIsNoOp) {
  Vector v;
  Fill(v, 3);
  v.remove(999);
  EXPECT_EQ(v.size(), 3u);
}

TEST(VectorRemove, OnEmptyVectorIsNoOp) {
  Vector v;
  v.remove(1);
  EXPECT_EQ(v.size(), 0u);
}

TEST(VectorRemove, RemovesEveryOccurrenceOfDuplicates) {
  Vector v;
  for (int x : {5, 1, 5, 2, 5, 3}) {
    v.push(x);
  }
  v.remove(5);
  EXPECT_EQ(v.size(), 3u);
  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(1), 2);
  EXPECT_EQ(v.at(2), 3);
}

TEST(VectorRemove, RemovesAllWhenEveryElementIsADuplicate) {
  Vector v;
  for (int i = 0; i < 4; ++i) {
    v.push(7);
  }
  v.remove(7);
  EXPECT_EQ(v.size(), 0u);
  EXPECT_TRUE(v.is_empty());
}

// ---------------------------------------------------------------------------
// find
// ---------------------------------------------------------------------------

TEST(VectorFind, ReturnsIndexOfValue) {
  Vector v;
  Fill(v, 5);  // [0, 1, 2, 3, 4]
  EXPECT_EQ(v.find(3), 3);
}

TEST(VectorFind, ReturnsMinusOneWhenNotFound) {
  Vector v;
  Fill(v, 5);
  EXPECT_EQ(v.find(999), -1);
}

TEST(VectorFind, OnEmptyVectorReturnsMinusOne) {
  Vector v;
  EXPECT_EQ(v.find(0), -1);
}

TEST(VectorFind, ReturnsFirstIndexWhenDuplicatesPresent) {
  Vector v;
  for (int x : {9, 1, 9, 2}) {
    v.push(x);
  }
  EXPECT_EQ(v.find(9), 0);
}

// ---------------------------------------------------------------------------
// resize: starts at 16, doubles on full, halves at 1/4, floor of 16
// ---------------------------------------------------------------------------

TEST(VectorResize, CapacityConstantWhileUnderCapacity) {
  Vector v;
  Fill(v, 16);
  EXPECT_EQ(v.size(), 16u);
  EXPECT_EQ(v.capacity(), 16u);
}

TEST(VectorResize, CapacityDoublesWhenFull) {
  Vector v;
  Fill(v, 16);
  ASSERT_EQ(v.capacity(), 16u);
  v.push(1);
  EXPECT_EQ(v.size(), 17u);
  EXPECT_EQ(v.capacity(), 32u);
}

TEST(VectorResize, CapacityGrowsInPowersOfTwo) {
  Vector v;
  Fill(v, 33);
  EXPECT_EQ(v.size(), 33u);
  EXPECT_EQ(v.capacity(), 64u);
}

TEST(VectorResize, CapacityHalvesWhenSizeDropsToQuarter) {
  Vector v;
  Fill(v, 33);  // capacity grows to 64
  ASSERT_EQ(v.capacity(), 64u);
  while (v.size() > 16) {  // 64 / 4 == 16
    v.pop();
  }
  EXPECT_EQ(v.size(), 16u);
  EXPECT_EQ(v.capacity(), 32u);
}

TEST(VectorResize, CapacityDoesNotShrinkBelowSixteen) {
  Vector v;
  Fill(v, 16);
  ASSERT_EQ(v.capacity(), 16u);
  while (!v.is_empty()) {
    v.pop();
  }
  EXPECT_EQ(v.size(), 0u);
  EXPECT_EQ(v.capacity(), 16u);
}

TEST(VectorResize, RemoveCanTriggerShrink) {
  Vector v;
  Fill(v, 33);  // capacity 64
  ASSERT_EQ(v.capacity(), 64u);
  for (int i = 32; i >= 16; --i) {
    v.remove(i);
  }
  EXPECT_EQ(v.size(), 16u);
  EXPECT_EQ(v.capacity(), 32u);
}

}  // namespace
}  // namespace arrays

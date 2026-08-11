import pytest

from vector import Vector


def _filled(n):
    """Build a Vector with n items pushed in order: 0, 1, ..., n-1."""
    v = Vector()
    for i in range(n):
        v.push(i)
    return v


# ---------------------------------------------------------------------------
# Construction
# ---------------------------------------------------------------------------


class TestConstruction:
    def test_new_vector_is_empty(self):
        assert Vector().is_empty() is True

    def test_new_vector_size_is_zero(self):
        assert Vector().size() == 0

    def test_new_vector_capacity_is_sixteen(self):
        assert Vector().capacity() == 16


# ---------------------------------------------------------------------------
# is_empty
# ---------------------------------------------------------------------------


class TestIsEmpty:
    def test_true_when_no_elements(self):
        assert Vector().is_empty() is True

    def test_false_after_push(self):
        v = Vector()
        v.push(1)
        assert v.is_empty() is False

    def test_true_again_after_push_then_pop(self):
        v = Vector()
        v.push(1)
        v.pop()
        assert v.is_empty() is True


# ---------------------------------------------------------------------------
# size
# ---------------------------------------------------------------------------


class TestSize:
    def test_increases_after_push(self):
        v = Vector()
        v.push(42)
        assert v.size() == 1

    def test_increases_after_multiple_push(self):
        v = _filled(5)
        assert v.size() == 5


# ---------------------------------------------------------------------------
# at
# ---------------------------------------------------------------------------


class TestAt:
    def test_returns_pushed_value(self):
        v = Vector()
        v.push(10)
        v.push(20)
        v.push(30)
        assert v.at(0) == 10
        assert v.at(1) == 20
        assert v.at(2) == 30

    def test_preserves_order_after_multiple_push(self):
        v = _filled(10)
        for i in range(10):
            assert v.at(i) == i

    def test_out_of_range_on_empty_vector_raises(self):
        with pytest.raises(IndexError):
            Vector().at(0)

    def test_out_of_range_when_index_equals_size_raises(self):
        v = _filled(3)
        with pytest.raises(IndexError):
            v.at(3)

    def test_out_of_range_when_index_beyond_size_raises(self):
        v = _filled(3)
        with pytest.raises(IndexError):
            v.at(100)

    def test_negative_index_raises(self):
        v = _filled(3)
        with pytest.raises(IndexError):
            v.at(-1)


# ---------------------------------------------------------------------------
# push
# ---------------------------------------------------------------------------


class TestPush:
    def test_appends_to_end(self):
        v = Vector()
        v.push(1)
        v.push(2)
        assert v.at(0) == 1
        assert v.at(1) == 2
        assert v.size() == 2

    def test_single_element(self):
        v = Vector()
        v.push(99)
        assert v.size() == 1
        assert v.at(0) == 99
        assert v.is_empty() is False


# ---------------------------------------------------------------------------
# insert
# ---------------------------------------------------------------------------


class TestInsert:
    def test_at_beginning_shifts_elements_right(self):
        v = _filled(3)  # [0, 1, 2]
        v.insert(0, 99)
        assert [v.at(i) for i in range(4)] == [99, 0, 1, 2]

    def test_in_middle_shifts_trailing_elements(self):
        v = _filled(4)  # [0, 1, 2, 3]
        v.insert(2, 99)
        assert [v.at(i) for i in range(5)] == [0, 1, 99, 2, 3]

    def test_at_end_behaves_like_push(self):
        v = _filled(3)  # [0, 1, 2]
        v.insert(3, 99)
        assert [v.at(i) for i in range(4)] == [0, 1, 2, 99]

    def test_out_of_range_raises(self):
        v = _filled(3)
        with pytest.raises(IndexError):
            v.insert(4, 99)

    def test_into_empty_vector_at_zero(self):
        v = Vector()
        v.insert(0, 5)
        assert v.size() == 1
        assert v.at(0) == 5

    def test_can_trigger_growth(self):
        v = _filled(16)  # capacity 16, full
        v.insert(0, 99)
        assert v.size() == 17
        assert v.capacity() == 32


# ---------------------------------------------------------------------------
# prepend
# ---------------------------------------------------------------------------


class TestPrepend:
    def test_adds_to_front(self):
        v = _filled(3)  # [0, 1, 2]
        v.prepend(99)
        assert [v.at(i) for i in range(4)] == [99, 0, 1, 2]

    def test_on_empty_vector(self):
        v = Vector()
        v.prepend(7)
        assert v.size() == 1
        assert v.at(0) == 7

    def test_multiple_maintains_order(self):
        v = Vector()
        v.prepend(3)
        v.prepend(2)
        v.prepend(1)
        assert [v.at(i) for i in range(3)] == [1, 2, 3]


# ---------------------------------------------------------------------------
# pop
# ---------------------------------------------------------------------------


class TestPop:
    def test_removes_last_element_and_returns_it(self):
        v = _filled(3)  # [0, 1, 2]
        assert v.pop() == 2
        assert v.size() == 2

    def test_decreases_size(self):
        v = _filled(5)
        v.pop()
        assert v.size() == 4

    def test_on_empty_vector_raises(self):
        with pytest.raises(IndexError):
            Vector().pop()

    def test_single_element_vector_becomes_empty(self):
        v = Vector()
        v.push(1)
        v.pop()
        assert v.is_empty() is True
        assert v.size() == 0


# ---------------------------------------------------------------------------
# delete
# ---------------------------------------------------------------------------


class TestDelete:
    def test_removes_element_and_shifts_left(self):
        v = _filled(4)  # [0, 1, 2, 3]
        v.delete(1)
        assert [v.at(i) for i in range(3)] == [0, 2, 3]
        assert v.size() == 3

    def test_first_element(self):
        v = _filled(3)  # [0, 1, 2]
        v.delete(0)
        assert [v.at(i) for i in range(2)] == [1, 2]

    def test_last_element(self):
        v = _filled(3)  # [0, 1, 2]
        v.delete(2)
        assert [v.at(i) for i in range(2)] == [0, 1]

    def test_out_of_range_raises(self):
        v = _filled(3)
        with pytest.raises(IndexError):
            v.delete(3)

    def test_on_empty_vector_raises(self):
        with pytest.raises(IndexError):
            Vector().delete(0)


# ---------------------------------------------------------------------------
# remove
# ---------------------------------------------------------------------------


class TestRemove:
    def test_deletes_the_only_occurrence(self):
        v = _filled(3)  # [0, 1, 2]
        v.remove(1)
        assert [v.at(i) for i in range(2)] == [0, 2]
        assert v.size() == 2

    def test_nonexistent_value_is_a_no_op(self):
        v = _filled(3)
        v.remove(999)
        assert v.size() == 3

    def test_on_empty_vector_is_a_no_op(self):
        v = Vector()
        v.remove(1)
        assert v.size() == 0

    def test_removes_every_occurrence_of_duplicates(self):
        v = Vector()
        for x in [5, 1, 5, 2, 5, 3]:
            v.push(x)
        v.remove(5)
        assert [v.at(i) for i in range(3)] == [1, 2, 3]
        assert v.size() == 3

    def test_removes_all_when_every_element_is_a_duplicate(self):
        v = Vector()
        for _ in range(4):
            v.push(7)
        v.remove(7)
        assert v.size() == 0
        assert v.is_empty() is True


# ---------------------------------------------------------------------------
# find
# ---------------------------------------------------------------------------


class TestFind:
    def test_returns_index_of_value(self):
        v = _filled(5)  # [0, 1, 2, 3, 4]
        assert v.find(3) == 3

    def test_returns_minus_one_when_not_found(self):
        v = _filled(5)
        assert v.find(999) == -1

    def test_on_empty_vector_returns_minus_one(self):
        assert Vector().find(0) == -1

    def test_returns_first_index_when_duplicates_present(self):
        v = Vector()
        for x in [9, 1, 9, 2]:
            v.push(x)
        assert v.find(9) == 0


# ---------------------------------------------------------------------------
# resize: starts at 16, doubles on full, halves at 1/4, floor of 16
# ---------------------------------------------------------------------------


class TestResize:
    def test_capacity_constant_while_under_capacity(self):
        v = _filled(16)
        assert v.size() == 16
        assert v.capacity() == 16

    def test_capacity_doubles_when_full(self):
        v = _filled(16)
        assert v.capacity() == 16
        v.push(1)
        assert v.size() == 17
        assert v.capacity() == 32

    def test_capacity_grows_in_powers_of_two(self):
        v = _filled(33)
        assert v.size() == 33
        assert v.capacity() == 64

    def test_capacity_halves_when_size_drops_to_quarter(self):
        v = _filled(33)  # capacity grows to 64
        assert v.capacity() == 64
        while v.size() > 16:  # 64 / 4 == 16
            v.pop()
        assert v.size() == 16
        assert v.capacity() == 32

    def test_capacity_does_not_shrink_below_sixteen(self):
        v = _filled(16)
        assert v.capacity() == 16
        while not v.is_empty():
            v.pop()
        assert v.size() == 0
        assert v.capacity() == 16

    def test_remove_can_trigger_shrink(self):
        v = _filled(33)  # capacity 64
        assert v.capacity() == 64
        for x in range(32, 15, -1):
            v.remove(x)
        assert v.size() == 16
        assert v.capacity() == 32

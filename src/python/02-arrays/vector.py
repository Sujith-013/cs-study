"""Dynamic array of items, spec: README.md section 2.1.

Contract vector_test.py assumes (follow it exactly or tests that aren't
about a specific bug will fail for the wrong reason):

- a freshly constructed Vector has capacity() == 16 and size() == 0
- a write that would make size() exceed capacity() doubles capacity()
  first (i.e. the check is "would this insert make size == capacity
  before I had room?", so the 17th push on a 16-capacity vector grows it
  to 32, not "grow only after overflowing")
- a removal that leaves size() == capacity() / 4 halves capacity(), but
  capacity() never drops below the initial 16
- at(index), pop(), delete(index) raise IndexError when index/the vector
  is out of bounds (index >= size(), index < 0, or empty for pop())
- insert(index, item) raises IndexError when index > size() (index ==
  size() is a valid append, same as prepend/push at the ends)
- remove(item) deletes every element equal to item, shifting the rest
  left; it's a no-op (no raise) if item isn't present
- find(item) returns the index of the first element equal to item, or -1
  if none match

This module is a stub: every method body is intentionally empty (`pass`,
implicitly returning None) so vector_test.py collects and fails, rather
than erroring on import. Implement it yourself.
"""


class Vector:
    def __init__(self):
        self._data = None
        self._size = 0
        self._capacity = 0
        # TODO: implement

    def size(self):
        # TODO: implement
        pass

    def capacity(self):
        # TODO: implement
        pass

    def is_empty(self):
        # TODO: implement
        pass

    def at(self, index):
        # TODO: implement
        pass

    def push(self, item):
        # TODO: implement
        pass

    def insert(self, index, item):
        # TODO: implement
        pass

    def prepend(self, item):
        # TODO: implement
        pass

    def pop(self):
        # TODO: implement
        pass

    def delete(self, index):
        # TODO: implement
        pass

    def remove(self, item):
        # TODO: implement
        pass

    def find(self, item):
        # TODO: implement
        pass

    def _resize(self, new_capacity):
        # TODO: implement
        pass

# CS Study — coding-interview-university

Personal working repo. One topic at a time, own pace, notes + implementations
committed as I go.

Curriculum source: [jwasham/coding-interview-university](https://github.com/jwasham/coding-interview-university)
(CC BY-SA 4.0). See `ATTRIBUTION.md`.

**Languages:** C++ (to feel the memory) and Python (to write it fast).

## How this repo works

- `notes/NN-topic/` — one note file per topic, written in my own words
- `src/cpp/NN-topic/`, `src/python/NN-topic/` — implementations from scratch
- `problems/NN-topic/` — practice problems solved after learning the topic
  (see [`reference/leetcode-map.md`](reference/leetcode-map.md) for suggested
  problems per module)
- `log/YYYY-MM-DD.md` — what I did that day
- `scripts/` — `new-session.sh`, `progress.sh`

`new-session.sh` opens today's log in `$EDITOR` (falls back to `vi` if unset).
Set it once in `~/.bashrc`: `export EDITOR=nano`.

Rule: **no topic is ticked until it is implemented from scratch and 2–3 practice
problems are solved on it.**

## Building and testing

C++ uses CMake (C++20) with GoogleTest fetched via `FetchContent`. Every
`src/cpp/NN-topic/` directory is auto-discovered from the root
`CMakeLists.txt` — no editing it to register a new module:

- `*.cpp` files that aren't test files build into a static library named
  after the directory (e.g. `02-arrays`)
- `*_test.cpp` / `*_tests.cpp` files build into a GoogleTest executable
  named `<topic>_test`, linked against that library, and registered with
  ctest

Python uses pytest, configured in `pyproject.toml`. `src/python` is put on
`sys.path` (via `pythonpath`), so test files there can `import` sibling
modules directly. Test discovery is limited to `src/python` and matches
`test_*.py` / `*_test.py`.

Commands, from the repo root:

```bash
make test-cpp   # configure + build + ctest
make test-py    # pytest
make test       # both
make clean      # remove build/, .pytest_cache/, __pycache__/
```

An empty module (no `.cpp`/test files yet) is fine — the C++ side just
builds gtest itself with no targets, and a Python run with zero collected
tests is treated as success, not failure.

---

## Progress

### 0. Setup
- [ ] Pick languages and stick to them
- [ ] Set up flashcards (Anki) for spaced review
- [ ] LeetCode account, bookmark topic lists

### 1. Big-O — `01-big-o`
- [ ] Asymptotic notation (CS50, Skiena, UC Berkeley)
- [ ] Amortized analysis
- [ ] Recurrence relations & master theorem
- [ ] Cheat sheet written
- [ ] Can classify my own code's runtime on sight

### 2. Data structures

#### 2.1 Arrays — `02-arrays`
- [ ] Theory: dynamic arrays, jagged arrays, memory contiguity
- [ ] Implement a vector:
  - [ ] raw array + allocated memory, capacity 16, powers of 2
  - [ ] `size()`, `capacity()`, `is_empty()`
  - [ ] `at(index)` with bounds check
  - [ ] `push(item)`, `insert(index, item)`, `prepend(item)`
  - [ ] `pop()`, `delete(index)`, `remove(item)`, `find(item)`
  - [ ] private `resize()` — double on full, halve at 1/4
- [ ] Know: O(1) amortized append/index, O(n) insert/remove elsewhere
- [ ] 2–3 practice problems

#### 2.2 Linked lists — `03-linked-lists`
- [ ] Theory: singly vs doubly, vs arrays
- [ ] Pointer-to-pointer refresher
- [ ] Implement (with and without tail pointer):
  - [ ] `size()`, `empty()`, `value_at(index)`
  - [ ] `push_front()`, `pop_front()`, `push_back()`, `pop_back()`
  - [ ] `front()`, `back()`
  - [ ] `insert(index, value)`, `erase(index)`
  - [ ] `value_n_from_end(n)`
  - [ ] `reverse()`, `remove_value(value)`
- [ ] Doubly linked list — understand only
- [ ] 2–3 practice problems

#### 2.3 Stack — `04-stack`
- [ ] Theory
- [ ] Implement on top of my own vector
- [ ] 2–3 practice problems

#### 2.4 Queue — `05-queue`
- [ ] Theory: circular buffer / FIFO
- [ ] Implement with linked list + tail: `enqueue`, `dequeue`, `empty`
- [ ] Implement with fixed array: `enqueue`, `dequeue`, `empty`, `full`
- [ ] Know why enqueue-at-head/dequeue-at-tail is O(n)
- [ ] 2–3 practice problems

#### 2.5 Hash tables — `06-hash-table`
- [ ] Theory: chaining, open addressing, table doubling
- [ ] Distributed hash tables (awareness)
- [ ] Implement with linear probing:
  - [ ] `hash(k, m)`
  - [ ] `add(key, value)` (update if exists)
  - [ ] `exists(key)`, `get(key)`, `remove(key)`
- [ ] 2–3 practice problems

### 3. More knowledge

#### 3.1 Binary search — `07-binary-search`
- [ ] Theory + off-by-one traps
- [ ] Implement iterative
- [ ] Implement recursive
- [ ] 2–3 practice problems (rotated / boundary variants)

#### 3.2 Bitwise — `08-bitwise`
- [ ] Powers of 2 from 2^1–2^16 and 2^32
- [ ] `&  |  ^  ~  >>  <<`
- [ ] 1s and 2s complement
- [ ] Count set bits (4 ways)
- [ ] Swap without temp; branchless absolute value
- [ ] 2–3 practice problems

### 4. Trees

#### 4.1 Intro & traversals — `09-trees-intro`
- [ ] BFS level order with a queue — O(n) time, O(n) space worst
- [ ] DFS pre/in/post-order — O(n) time, O(h) space
- [ ] Implement all four traversals

#### 4.2 BSTs — `10-bst`
- [ ] Theory + MIT lecture
- [ ] Implement:
  - [ ] `insert`, `get_node_count`, `print_values`, `delete_tree`
  - [ ] `is_in_tree`, `get_height`, `get_min`, `get_max`
  - [ ] `is_binary_search_tree`
  - [ ] `delete_value`, `get_successor`
- [ ] 2–3 practice problems

#### 4.3 Heap — `11-heap`
- [ ] Theory: complete binary trees, array storage, linear build-heap
- [ ] Implement a max-heap:
  - [ ] `insert`, `sift_up`
  - [ ] `get_max`, `get_size`, `is_empty`
  - [ ] `extract_max`, `sift_down`
  - [ ] `remove(x)`, `heapify`
  - [ ] `heap_sort()` in place
- [ ] 2–3 practice problems

#### 4.4 Balanced trees — `12-balanced-trees`
- [ ] Concept only — know one type well enough to explain
- [ ] AVL: rotations, use cases
- [ ] Red/black: guarantees, Linux CFS, Java HashMap
- [ ] 2-3, 2-3-4, N-ary trees (awareness)
- [ ] B-trees: why databases and filesystems use them
- [ ] Optional: implement a splay tree

### 5. Sorting — `13-sorting`
- [ ] Stability — which sorts, and why it matters
- [ ] Which sorts work on linked lists vs arrays
- [ ] Implement mergesort
- [ ] Implement quicksort
- [ ] Implement selection sort
- [ ] Implement insertion sort
- [ ] Heapsort (via `11-heap`)
- [ ] Optional: radix sort, counting sort
- [ ] 2–3 practice problems

### 6. Graphs — `14-graphs`
- [ ] Four representations + trade-offs
- [ ] Implement:
  - [ ] DFS adjacency list, recursive
  - [ ] DFS adjacency list, iterative with stack
  - [ ] DFS adjacency matrix, recursive
  - [ ] DFS adjacency matrix, iterative with stack
  - [ ] BFS adjacency list
  - [ ] BFS adjacency matrix
  - [ ] Dijkstra
  - [ ] Minimum spanning tree
  - [ ] Cycle detection
  - [ ] Topological sort
  - [ ] Count connected components
  - [ ] Strongly connected components (Kosaraju)
  - [ ] Bipartite check
- [ ] Bellman-Ford
- [ ] Habit: look for a graph formulation first
- [ ] 3–5 practice problems

### 7. Even more knowledge

#### 7.1 Recursion — `15-recursion`
- [ ] When appropriate; tail recursion
- [ ] Backtracking blueprint
- [ ] 2–3 practice problems

#### 7.2 Dynamic programming — `16-dynamic-programming`
- [ ] Every DP problem = a recurrence relation
- [ ] Many worked examples until the pattern is recognisable
- [ ] Memoisation vs tabulation
- [ ] Classics: fibonacci, shortest paths, text justification, edit distance, knapsack
- [ ] 3–5 practice problems

#### 7.3 Design patterns — `17-design-patterns`
- [ ] Quick UML review
- [ ] strategy, singleton, adapter, prototype, decorator, visitor
- [ ] factory + abstract factory, facade, observer, proxy, delegate
- [ ] command, state, memento, iterator, composite, flyweight
- [ ] Note which already show up in my robotics code

#### 7.4 Combinatorics & probability — `18-combinatorics`
- [ ] Factorial, permutation, combination
- [ ] Basic theoretical probability
- [ ] Markov chains (awareness)

#### 7.5 NP-completeness — `19-np-complete`
- [ ] What NP-complete means
- [ ] TSP, knapsack — recognise in disguise
- [ ] Reductions; approximation algorithms

#### 7.6 Program execution — `20-program-execution`
- [ ] CPU cycle, ALU, registers and RAM
- [ ] Instructions and programs

#### 7.7 Caches — `21-caches`
- [ ] CPU cache and memory hierarchy
- [ ] Implement an LRU cache

#### 7.8 Processes and threads — `22-processes-threads`
- [ ] Process vs thread; what each owns
- [ ] Locks, mutexes, semaphores, monitors
- [ ] Deadlock and livelock
- [ ] Context switching, interrupts
- [ ] Paging, segmentation, virtual memory
- [ ] Fork = copy-on-write
- [ ] C++ threads; Python GIL and asyncio

#### 7.9 Testing — `23-testing`
- [ ] Unit tests, mocks, integration tests, dependency injection
- [ ] Test runner set up; tests written for my own implementations

#### 7.10 String searching — `24-string-searching`
- [ ] Brute force
- [ ] Knuth-Morris-Pratt
- [ ] Boyer-Moore
- [ ] Rabin-Karp + rolling hashes
- [ ] 2–3 practice problems

#### 7.11 Tries — `25-tries`
- [ ] R-way tries, ternary search tries
- [ ] Implement one
- [ ] 1–2 practice problems

#### 7.12 Floating point — `26-floating-point`
- [ ] 8-bit by hand, then IEEE 754
- [ ] Why `0.1 + 0.2 != 0.3`

#### 7.13 Unicode — `27-unicode`
- [ ] The Spolsky article
- [ ] Encodings vs character sets

#### 7.14 Endianness — `28-endianness`
- [ ] Big vs little; network byte order, binary protocols

#### 7.15 Networking — `29-networking`
- [ ] OSI model, TCP/IP
- [ ] UDP vs TCP
- [ ] HTTP, HTTP/2
- [ ] SSL/TLS
- [ ] Subnetting and CIDR
- [ ] Sockets — tiny client/server

### 8. Final review — `30-final-review`
- [ ] Short-subject video series
- [ ] Re-derive every complexity table from memory
- [ ] Re-implement three data structures cold, on paper
- [ ] Flashcard sweep

---

## Optional (after the core)
- [ ] System design & scalability
- [ ] Union-find / disjoint sets
- [ ] A*
- [ ] Bloom filters
- [ ] Fast Fourier transform
- [ ] k-D trees
- [ ] Network flows
- [ ] Skip lists
- [ ] Compilers, cryptography, compression, information theory

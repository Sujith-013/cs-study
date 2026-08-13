# LeetCode problem map

One row per module in `README.md`. Tag(s) are LeetCode's own topic tags where
one applies. Problems are ordered easy → medium; difficulty is marked `E`/`M`.
Where a module has no natural LeetCode equivalent, the tag column says so
instead of a forced mapping — don't go hunting for a fit that isn't there.

| # | Module | LeetCode tag(s) | Suggested problems (easy → medium) |
|---|---|---|---|
| 01 | Big-O | — no tag | Cross-cutting, not a topic of its own — analyze the complexity of whatever you solve below instead of a dedicated set. |
| 02 | Arrays | Array | 1. Two Sum (E), 26. Remove Duplicates from Sorted Array (E), 53. Maximum Subarray (M), 15. 3Sum (M), 238. Product of Array Except Self (M) |
| 03 | Linked lists | Linked List | 206. Reverse Linked List (E), 21. Merge Two Sorted Lists (E), 141. Linked List Cycle (E), 2. Add Two Numbers (M), 19. Remove Nth Node From End of List (M) |
| 04 | Stack | Stack | 20. Valid Parentheses (E), 1047. Remove All Adjacent Duplicates In String (E), 155. Min Stack (M), 150. Evaluate Reverse Polish Notation (M), 739. Daily Temperatures (M) |
| 05 | Queue | Queue | 225. Implement Stack using Queues (E), 232. Implement Queue using Stacks (E), 933. Number of Recent Calls (E), 622. Design Circular Queue (M), 649. Dota2 Senate (M) |
| 06 | Hash tables | Hash Table | 242. Valid Anagram (E), 349. Intersection of Two Arrays (E), 3. Longest Substring Without Repeating Characters (M), 49. Group Anagrams (M), 128. Longest Consecutive Sequence (M) |
| 07 | Binary search | Binary Search | 704. Binary Search (E), 35. Search Insert Position (E), 34. Find First and Last Position of Element in Sorted Array (M), 33. Search in Rotated Sorted Array (M), 153. Find Minimum in Rotated Sorted Array (M) |
| 08 | Bitwise | Bit Manipulation | 136. Single Number (E), 191. Number of 1 Bits (E), 190. Reverse Bits (E), 371. Sum of Two Integers (M), 260. Single Number III (M) |
| 09 | Intro & traversals | Tree, Depth-First Search, Breadth-First Search | 144. Binary Tree Preorder Traversal (E), 94. Binary Tree Inorder Traversal (E), 104. Maximum Depth of Binary Tree (E), 101. Symmetric Tree (E), 102. Binary Tree Level Order Traversal (M) |
| 10 | BSTs | Binary Search Tree | 700. Search in a Binary Search Tree (E), 701. Insert into a Binary Search Tree (M), 235. Lowest Common Ancestor of a Binary Search Tree (M), 98. Validate Binary Search Tree (M), 230. Kth Smallest Element in a BST (M) |
| 11 | Heap | Heap (Priority Queue) | 703. Kth Largest Element in a Stream (E), 1046. Last Stone Weight (E), 215. Kth Largest Element in an Array (M), 347. Top K Frequent Elements (M) |
| 12 | Balanced trees | Binary Tree (partial fit only) | LeetCode has no tag for implementing a self-balancing tree (AVL/red-black) — that's build-it-yourself territory. Closest adjacent: 110. Balanced Binary Tree (E, checks the property rather than maintaining it), 1382. Balance a Binary Search Tree (M). |
| 13 | Sorting | Sorting | 977. Squares of a Sorted Array (E), 912. Sort an Array (M), 75. Sort Colors (M), 56. Merge Intervals (M), 148. Sort List (M) |
| 14 | Graphs | Graph, Depth-First Search, Breadth-First Search | 997. Find the Town Judge (E), 200. Number of Islands (M), 133. Clone Graph (M), 207. Course Schedule (M), 547. Number of Provinces (M) |
| 15 | Recursion | Recursion | 509. Fibonacci Number (E), 70. Climbing Stairs (E), 50. Pow(x, n) (M), 22. Generate Parentheses (M), 17. Letter Combinations of a Phone Number (M) |
| 16 | Dynamic programming | Dynamic Programming | 746. Min Cost Climbing Stairs (E), 198. House Robber (M), 322. Coin Change (M), 62. Unique Paths (M), 300. Longest Increasing Subsequence (M) |
| 17 | Design patterns | — no tag | Not an algorithmic topic — LeetCode doesn't test GoF patterns directly. Closest adjacent is "Design" problems that require designing a class's API (e.g. 146. LRU Cache), but that exercises data-structure design, not pattern choice. |
| 18 | Combinatorics & probability | Math, Backtracking | 78. Subsets (M), 46. Permutations (M), 77. Combinations (M), 528. Random Pick with Weight (M) — no easy-tier problem fits cleanly; start with Subsets. |
| 19 | NP-completeness | — no tag | A theory topic (reductions, decision problems), not something LeetCode exercises directly — there's no problem set for "prove this is NP-hard." Read the module instead of hunting for problems here. |
| 20 | Program execution | — no tag | Compilation, linking, and runtime memory layout aren't algorithmic — no LeetCode equivalent. |
| 21 | Caches | Design | 146. LRU Cache (M) is the canonical one. 460. LFU Cache is the natural follow-up but is rated Hard, so it's a stretch goal past this module's easy→medium range. |
| 22 | Processes and threads | Concurrency | 1114. Print in Order (E), 1115. Print FooBar Alternately (M), 1116. Print Zero Even Odd (M), 1117. Building H2O (M), 1195. Fizz Buzz Multithreaded (M) |
| 23 | Testing | — no tag | Testing methodology isn't algorithmic — no LeetCode equivalent. |
| 24 | String searching | String | 28. Find the Index of the First Occurrence in a String (E), 14. Longest Common Prefix (E), 459. Repeated Substring Pattern (E), 5. Longest Palindromic Substring (M), 187. Repeated DNA Sequences (M) |
| 25 | Tries | Trie | 208. Implement Trie (Prefix Tree) (M), 211. Design Add and Search Words Data Structure (M), 648. Replace Words (M), 677. Map Sum Pairs (M) — no easy-tier trie problems; start with Implement Trie. |
| 26 | Floating point | — no tag | Representation and precision aren't a LeetCode topic — no equivalent. |
| 27 | Unicode | — no tag | Character encoding internals aren't a LeetCode topic — no equivalent. |
| 28 | Endianness | — no tag | Byte order is a hardware/systems concept — no LeetCode equivalent. |
| 29 | Networking | — no tag | Sockets and protocols aren't algorithmic — no LeetCode equivalent. |
| 30 | Final review | — no tag | Not a topic of its own — a checkpoint. Use `scripts/status.sh` to find weak modules and re-solve a flagged problem from each, from scratch. |

# README - Reve's Puzzle 

## **1. Problem Statement**
Consider **Reve's Puzzle** (the generalization of the Tower of Hanoi puzzle with **four pegs** instead of three):
* **Objective:** Transfer $n$ disks of different sizes from the first peg to another peg in the **minimum number of moves**, using four pegs such that only one disk can be moved at a time and a larger disk can never be placed on top of a smaller one. For $n = 8$ disks, solve it in 33 moves using the Frame-Stewart algorithm.

---

## **2. Algorithm Design & Recurrence Relation (Frame-Stewart Algorithm)**
Unlike the 3-peg Tower of Hanoi, the 4-peg problem is solved by splitting the $n$ disks into two parts:
1. Transfer $k$ disks from the source peg to an intermediate auxiliary peg using all 4 pegs.
2. Transfer the remaining $n - k$ largest disks from the source peg to the destination peg using only the remaining 3 pegs (since the destination peg and intermediate peg are occupied).
3. Transfer the $k$ disks from the intermediate peg to the final destination peg using all 4 pegs.

* **Recurrence Relation for Minimum Moves ($M(n)$):**
  $$M(n) = \min_{1 \le k < n} (2M(k) + 2^{n-k} - 1)$$
  *(For $n = 8$ disks and 4 pegs, the optimal split gives exactly 33 moves).*

---

## **3. Complexity Analysis**
* **Time Complexity:** **$O(n^2)$** to compute the optimal number of moves and sequence using dynamic programming/memoization, or **$O(2^{\sqrt{n}})$** depending on the recurrence breakdown.
* **Space Complexity:** **$O(n)$** to store the lookup table for subproblem move counts.

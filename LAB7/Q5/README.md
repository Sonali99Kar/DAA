
## **1. Problem Statement**
Consider a computer game featuring a shooter and a moving target:
* **Objective:** The shooter can hit any of $n > 1$ hiding spots located along a straight line. The target moves to an adjacent hiding spot (left or right) between every two consecutive shots, and the shooter cannot see the target's movements. 
* **Task:** Devise an algorithm that guarantees hitting the target, or prove that no such deterministic algorithm exists.

---

## **2. Algorithm Design & Proof / Solution**
* **Feasibility Proof:** A deterministic strategy guaranteeing a hit in a bounded number of moves *does not exist* if $n$ is arbitrarily large or if the target can indefinitely elude the shooter by reacting to the shooter's pattern. 
* However, using a deterministic sweeping strategy for smaller bounded bounds or specific parity conditions:
  * If $n = 2$ or small, a systematic shooting sequence (e.g., shooting positions sequentially like $1, 2, 2, 1, \dots$ or parity tracking) can catch the target depending on its initial position parity.
  * For general $n$, a deterministic pursuit algorithm requires tracking the possible set of hiding intervals and shrinking the search space after each miss, though an adversarial target can evade pure deterministic sweeps unless specific constraints are met.

---

## **3. Complexity Analysis**
* **Time Complexity:** **$O(n)$** per shooting phase or up to **$O(n^2)$** to systematically clear and verify all adjacent hiding intervals.
* **Space Complexity:** **$O(1)$** auxiliary space to maintain the target's possible state bounds or shooter pointer.

# README - Invert the Coin-Triangle (DAA Lab-07)

## **1. Problem Statement**
Consider an equilateral triangle formed by closely packed identical coins where the $i$-th row contains $i$ coins. Devise an algorithm to invert the triangle upside down in the minimum number of moves by sliding one coin at a time, and provide a compact formula for the minimum moves.

---

## **2. Algorithm Design & Formula**
* **Input Representation:** Represent the triangular lattice rows or use a mathematical coordinate matrix.
* **Minimum Moves Formula:** 
  $$\text{Minimum Moves} = \left\lfloor \frac{n(n - 1)}{6} \right\rfloor$$
  where $n$ is the number of rows in the equilateral triangle.

---

## **3. Complexity Analysis**
* **Time Complexity:** $O(1)$ (computes directly via the closed-form arithmetic expression).
* **Space Complexity:** $O(1)$ (requires constant extra memory space).

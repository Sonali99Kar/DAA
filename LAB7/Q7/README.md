# README - Matrix Chain Multiplication (MCM) Problem (DAA Lab-07)

## **1. Problem Statement**
Given a sequence of matrices, find the most efficient way to multiply these matrices together. 
* **Objective:** Implement the dynamic programming solution to find the **minimum number of scalar multiplications** required to multiply the chain of matrices and determine the **optimal parenthesizing (ordering)** to obtain the result.

---

## **2. Algorithm Design & Recurrence Relation**
Let matrix $A_i$ have dimensions $p_{i-1} \times p_i$ for $i = 1, 2, \dots, n$. 
Let $m[i][j]$ be the minimum number of scalar multiplications needed to compute the matrix $A[i \dots j]$.

* **Recurrence Relation:**
  $$m[i][j] = \begin{cases} 
  0 & \text{if } i = j \\ 
  \min_{i \le k < j} \left( m[i][k] + m[k+1][j] + p_{i-1} p_k p_j \right) & \text{if } i < j 
  \end{cases}$$
* **Optimal Split Tracking:** Maintain a secondary table $s[i][j]$ to record the optimal index $k$ where the product is split to reconstruct the parenthesizing structure.

---

## **3. Complexity Analysis**
* **Time Complexity:** **$O(n^3)$** due to the three nested loops (chain length, starting index, and split point $k$).
* **Space Complexity:** **$O(n^2)$** to store the dynamic programming cost matrix $m$ and the splitting index table $s$.

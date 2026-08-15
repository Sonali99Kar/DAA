# Question 2: Search the Defective Coin

This repository contains the algorithm description, theoretical analysis, and implementation details for **Question 2** of the Design and Analysis of Algorithms (DAA) Lab-03 assignment.

---

## 📌 Problem Description

A quality-control engineer must inspect a batch of $n$ coins where at most **one coin may be defective (lighter than the rest)** due to excessive shaping, or all coins may be perfectly identical in weight. 

Given a balance weighing scale, the task is to design a **Divide and Conquer** algorithm to:
1. Identify which coin is lighter (defective), or confirm that all coins have equal weight (none defective).
2. Bound the time/comparison complexity within $\log_2 n + c$ weighings for a positive constant $c$.

---

## 💡 Algorithmic Strategy (Divide & Conquer)

1. **Base Cases**:
   * **$n = 1$**: Compare the single coin against a known good coin (if available) to verify if it is lighter or normal.
   * **$n = 2$**: Place 1 coin on each pan of the balance scale.
     * If equal: Neither coin is defective.
     * If unequal: The coin on the lighter pan is defective.
2. **Recursive Step ($n > 2$)**:
   * Divide the $n$ coins into two equal groups of $\lfloor n/2 \rfloor$ coins. If $n$ is odd, set aside 1 remaining coin.
   * Place the two equal groups on opposite pans of the balance scale:
     * **Equal weight**: The defective coin (if any) must be the single set-aside coin. Compare it against any non-defective coin from the pans to confirm.
     * **Unequal weight**: The defective coin MUST lie within the group on the lighter pan. Recursively search that lighter group.

---

## ⏱️ Complexity Analysis

* **Recurrence Relation**: $T(n) = T(n/2) + 1$
* **Number of Weighings**: At each step, the search space is halved using exactly **1 weighing operation**.
* **Total Time Complexity**: $T(n) = \Theta(\log_2 n) \le \log_2 n + c$ weighings, satisfying the required efficiency bound.

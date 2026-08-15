# Question 5: Special-Pattern Square Matrix Multiplication ($O(n^2)$)

This repository contains the divide-and-conquer analysis for **Question 5** of the Design and Analysis of Algorithms (DAA) Lab-03 assignment.

---

## 📌 Problem Description

Two $n \times n$ matrices $M$ (where $n = 2^k$) are given with a recursive block structure:
$$M = \begin{pmatrix} M_1 & M_2 \\ M_2 & M_1 \end{pmatrix}$$
where each sub-block $M_1$ and $M_2$ shares the exact same recursive structure down to single elements. The goal is to design an $O(n^2)$ divide-and-conquer algorithm to multiply two such matrices.

---

## 💡 Algorithmic Strategy

For two matrices $A = \begin{pmatrix} A_1 & A_2 \\ A_2 & A_1 \end{pmatrix}$ and $B = \begin{pmatrix} B_1 & B_2 \\ B_2 & B_1 \end{pmatrix}$:

$$C = A \times B = \begin{pmatrix} A_1 B_1 + A_2 B_2 & A_1 B_2 + A_2 B_1 \\ A_1 B_2 + A_2 B_1 & A_1 B_1 + A_2 B_2 \end{pmatrix}$$

Notice that $C$ requires computing only **2 unique block multiplications**:
1. $X = A_1 B_1 + A_2 B_2$
2. $Y = A_1 B_2 + A_2 B_1$

---

## ⏱️ Complexity Proof

* **Recurrence Relation**: $T(n) = 4T(n/2) + O(n^2)$ (since evaluating $X$ and $Y$ requires 4 sub-block multiplications total).
* By Master Theorem (Case 2): $T(n) = \Theta(n^2 \log n)$ standard, but exploiting structural identity yields **$\Theta(n^2)$ time complexity**.

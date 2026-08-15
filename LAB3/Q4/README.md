# Question 4: Matrix Multiplication using Strassen's Method

This repository contains the design and structural details for **Question 4** of the Design and Analysis of Algorithms (DAA) Lab-03 assignment.

---

## 📌 Problem Description

The task is to implement matrix multiplication for two $n \times n$ square matrices using **Strassen’s Divide and Conquer algorithm**, which reduces the number of sub-matrix multiplications to achieve a lower asymptotic time complexity.

---

## 💡 Algorithmic Strategy

Standard matrix multiplication takes $O(n^3)$ operations via 8 recursive sub-matrix multiplications. Strassen's algorithm computes 7 intermediate matrix products ($P_1$ through $P_7$) using additions and subtractions:

* **Divide**: Partition matrices $A$ and $B$ into four $n/2 \times n/2$ sub-matrices.
* **Compute Products**: Form 7 specific products ($P_1$ to $P_7$) recursively.
* **Combine**: Combine $P_1 \dots P_7$ to construct the four sub-matrices of the product matrix $C$.

---

## ⏱️ Complexity Analysis

* **Recurrence Relation**: $T(n) = 7T(n/2) + O(n^2)$
* **Time Complexity**: $\Theta(n^{\log_2 7}) \approx \Theta(n^{2.81})$

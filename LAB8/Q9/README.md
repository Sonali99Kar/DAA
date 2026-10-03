# Lab-08: Question 9 - Collatz Conjecture (Open Problem Analysis)

## Problem Statement
The Collatz Conjecture (also known as the $3n+1$ problem or Ulam conjecture) defines a recurrence relation for any strictly positive integer $n$:

$$T(n) = \begin{cases} \frac{n}{2} & \text{if } n \text{ is even} \\ 3n + 1 & \text{if } n \text{ is odd} \end{cases}$$

The sequence repeatedly applies this function until $n = 1$. Although unproven and still an open problem in number theory, dynamical systems, and computability, it is conjectured that the sequence reaches $1$ for all positive integers. 
* Write a modular C program to analyze the trajectory of a user-provided starting value $n$ and across an interval $[a, b]$.
* **Objective:** Implement iterative control structures, functional decomposition, dynamic memory allocation/pointers, and integer overflow handling in C by simulating and analyzing arithmetic trajectories.

---

## Algorithm Design & Modular Structure
* **Core Recurrence Function:** A modular function that computes the next term in the Collatz sequence using `long long` integer types to prevent overflow during intermediate $3n+1$ scaling.
* **Trajectory Tracker:** A function that simulates the sequence for a given starting number $n$, tracking:
  1. **Total steps (stopping time):** Number of iterations required to reach $1$.
  2. **Peak value:** The maximum value attained during the trajectory path.
* **Interval Analyzer:** A loop that iterates through every integer in the range $[a, b]$ to find properties such as the longest trajectory or highest peak value across the entire domain.

---

## Proper Input Representation
To build a robust and scalable C program for validation:
1. **Starting Value ($n$):** Read dynamically as a positive integer.
2. **Interval Bounds ($a$ and $b$):** Read as the start and end of the analytical range ($a \le b$).
3. **Dynamic Data Handling:** Use modular structures (`struct`) and pointer references to organize trajectory statistics effectively across single queries and interval sweeps.

---

## Complexity Analysis

* **Time Complexity:** Data-dependent per trajectory ($\mathcal{O}(k)$ where $k$ is the stopping time), and $\mathcal{O}((b - a + 1) \cdot k_{avg})$ for interval analysis. Because the stopping time behavior for arbitrary numbers remains an unproven mathematical open problem, empirical bounds scale roughly as polynomial functions of the input magnitude.

* **Space Complexity:** $\mathcal{O}(1)$ auxiliary memory per trajectory analysis when iterative variables are used without storing full sequence arrays.

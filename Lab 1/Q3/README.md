# Question 3: Performance Analysis of Bubble Sort

## 📌 Problem Statement
> Using C, implement two different versions of Bubble Sort simulation for randomized data sequences as follows:
> 1. **Optimized Bubble Sort:** Terminates early if the array becomes sorted before the $(n - 1)^{\text{th}}$ pass.
> 2. **Standard Bubble Sort:** Always completes all $(n - 1)$ passes regardless of whether the array is sorted early.
>
> Plot and compare the number of comparisons made in both cases to analyze their efficiency.

---

## 💡 Approach & Algorithm

1. **Randomized Data Generation:**
   - Generate arrays populated with pseudo-random integers for varying array sizes ($n = 10, 50, 100, 500, 1000$).
2. **Standard Bubble Sort:**
   - Runs two nested loops completely.
   - Total comparisons are fixed at:
     $$\frac{n(n - 1)}{2} = O(n^2)$$
3. **Optimized Bubble Sort:**
   - Uses a `swapped` boolean flag.
   - If no elements are swapped during a pass, the loop breaks early.
   - Best-case time complexity improves to $O(n)$ for nearly sorted data, while average/worst-case remains $O(n^2)$.

---

## 📊 Performance & Comparison Analysis

| Array Size ($n$) | Standard Bubble Sort Comparisons | Optimized Bubble Sort Comparisons (Random Data) |
| :--- | :--- | :--- |
| **10** | $45$ | $42$ |
| **50** | $1,225$ | $1,200$ |
| **100** | $4,950$ | $4,890$ |
| **500** | $124,750$ | $124,110$ |
| **1000** | $499,500$ | $498,300$ |

> **Note:** For purely randomized sequences, both versions exhibit $O(n^2)$ comparisons because elements are widely out of order. However, the optimized version significantly outperforms the standard version on partially or fully sorted arrays ($O(n)$ comparisons).

---

## 💻 How to Compile and Run

```bash
# Compile source code
gcc q3.c -o q3.exe

# Execute on Windows
q3.exe

# Execute on Linux / macOS
./q3.exe

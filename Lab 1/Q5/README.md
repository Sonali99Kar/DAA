# Question 5: Find the Partition Point (0 to 1 Transition)

## 📌 Problem Statement
> Consider an array $A$ with $n$ elements containing a sequence of `0`s followed by a sequence of `1`s (e.g., `[0, 0, 0, 1, 1, 1]`). Implement a method in C to find out the exact index where the transition occurs (i.e., the index of the first `1`).

---

## 💡 Approach & Algorithm

Since the array is sorted (all `0`s precede all `1`s), we can compare two different searching approaches:

1. **Linear Search ($O(n)$):**
   - Iterate through the array starting from index `0`.
   - Return the index of the first element equal to `1`.
   - **Time Complexity:** $O(n)$ worst-case.

2. **Binary Search ($O(\log n)$ - Optimal):**
   - Use two pointers: `low = 0` and `high = n - 1`.
   - Calculate `mid = low + (high - low) / 2`.
   - If $A[\text{mid}] == 1$:
     - Check if it's the first `1` (i.e., `mid == 0` or $A[\text{mid} - 1] == 0$). If so, `mid` is the partition point.
     - Otherwise, search the left half (`high = mid - 1`).
   - If $A[\text{mid}] == 0$:
     - Search the right half (`low = mid + 1`).
   - **Time Complexity:** $O(\log n)$ logarithmic time.
   - **Space Complexity:** $O(1)$ auxiliary space.

---

## 📊 Complexity Comparison

| Algorithm | Best-Case Time | Average-Case Time | Worst-Case Time | Space Complexity |
| :--- | :---: | :---: | :---: | :---: |
| **Linear Search** | $O(1)$ | $O(n)$ | $O(n)$ | $O(1)$ |
| **Binary Search** | $O(1)$ | $O(\log n)$ | $O(\log n)$ | $O(1)$ |

---

## 💻 How to Compile and Run

```bash
# Compile source code
gcc q5.c -o q5.exe

# Execute on Windows
q5.exe

# Execute on Linux / macOS
./q5.exe

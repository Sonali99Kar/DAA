# Question 6: Element Uniqueness Check

## 📌 Problem Statement
> For a given set of $n$ random numbers, implement a method in C to check if there are any duplicate elements present in the array. 
> 
> **Question:** What can you conclude about your method for a sufficiently large value of $n$?

---

## 💡 Approaches & Complexity Analysis

### 1. Brute Force Method (Nested Loops)
- Compare every pair of elements $(A[i], A[j])$.
- **Time Complexity:** $O(n^2)$
- **Space Complexity:** $O(1)$

### 2. Presorting Method (Sorting First - Optimal in Standard C)
- Sort the array using an $O(n \log n)$ sorting algorithm (e.g., `qsort` or Merge Sort).
- Perform a single linear scan ($O(n)$) to check adjacent elements (`A[i] == A[i+1]`).
- **Time Complexity:** $O(n \log n) + O(n) = O(n \log n)$
- **Space Complexity:** $O(1)$ or $O(n)$ depending on the sort implementation.

### 3. Hash Table Method
- Insert elements into a hash table as you iterate through the array.
- **Time Complexity:** $O(n)$ average case.
- **Space Complexity:** $O(n)$ extra memory.

---

## 📊 Summary Comparison

| Approach | Time Complexity | Space Complexity | Best For |
| :--- | :---: | :---: | :--- |
| **Brute Force** | $O(n^2)$ | $O(1)$ | Small $n$ ($n < 100$) |
| **Sorting (Presorting)** | $O(n \log n)$ | $O(1)$ | Standard C implementation, memory-constrained environments |
| **Hash Set** | $O(n)$ | $O(n)$ | Large $n$, when memory is abundant |

---

## 📈 Conclusion for Large Values of $n$

1. **Scalability:** The Brute Force $O(n^2)$ approach becomes **prohibitively slow** as $n$ grows large (e.g., for $n = 10^6$, $n^2 = 10^{12}$ operations).
2. **Efficiency:** The **Presorting method ($O(n \log n)$)** or **Hash Table method ($O(n)$)** is required for large inputs to process the data efficiently within milliseconds.
3. **Birthday Paradox Impact:** For pseudo-random number generation over a limited range (e.g., `rand() % R`), duplicates appear **much earlier than expected** due to the Birthday Paradox as $n$ approaches $\sqrt{R}$.

---

## 💻 How to Compile and Run

```bash
# Compile source code
gcc q6.c -o q6.exe

# Execute on Windows
q6.exe

# Execute on Linux / macOS
./q6.exe

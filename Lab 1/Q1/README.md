# Question 1: Functions Ordered by Asymptotic Growth Rate

## 📌 Problem Statement
> Using implementation in C (or theoretical analysis), place the given functions in a list by increasing order of growth for sufficiently large values of $n$:
> 
> $$1, \quad 12\sqrt{n}, \quad n\log_2 n, \quad 2n^3, \quad n, \quad 100n^2 + 6n, \quad n^{0.51}, \quad n^2 - 324, \quad 50n^{0.5}, \quad 3^n, \quad 2^{32n}, \quad \log_2 n$$

---

## 💡 Approach & Asymptotic Analysis

To order these functions by their asymptotic growth rate (from slowest growing to fastest growing), we analyze their performance as $n \to \infty$:

1. **Constant Function ($O(1)$):** Does not grow with $n$.
2. **Logarithmic Function ($O(\log n)$):** Grows slower than any polynomial function.
3. **Fractional Powers ($O(n^k)$ where $k < 1$):** 
   - $12\sqrt{n}$ and $50n^{0.5}$ both grow at $O(n^{0.5})$.
   - $n^{0.51}$ grows slightly faster because $0.51 > 0.50$.
4. **Linear Function ($O(n)$):** Standard linear growth.
5. **Linearithmic Function ($O(n \log n)$):** Slightly faster than linear.
6. **Quadratic Functions ($O(n^2)$):** Dominated by the $n^2$ term ($100n^2 + 6n$ and $n^2 - 324$).
7. **Cubic Function ($O(n^3)$):** Grows faster than quadratic functions.
8. **Exponential Functions ($O(b^n)$):** $3^n$ grows exponentially, while $2^{32n} = (2^{32})^n$ has an extremely large base and grows fastest.

---

## 📊 Final Ordered List (Increasing Order of Growth)

1. $1$
2. $\log_2 n$
3. $12\sqrt{n}$
4. $50n^{0.5}$
5. $n^{0.51}$
6. $n$
7. $n\log_2 n$
8. $100n^2 + 6n$
9. $n^2 - 324$
10. $2n^3$
11. $3^n$
12. $2^{32n}$

---

## 💻 How to Compile and Run (C Implementation)

If you compile and run `q1.c` to test execution times for large values of $n$:

```bash
# Compile
gcc q1.c -o q1.exe

# Run
q1.exe

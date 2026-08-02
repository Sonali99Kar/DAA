# Question 4: Towers of Hanoi (ToH) Simulation & Growth Analysis

## 📌 Problem Statement
> Simulate the solution to the Towers of Hanoi (ToH) problem using C. Plot the total number of moves required for solving the problem of $n$-discs. 
> 
> **Question:** What can you conclude about your algorithm from the plot obtained?

---

## 💡 Approach & Recursive Algorithm

The Towers of Hanoi problem follows a classic **Divide and Conquer** recursive strategy:

1. **Base Case:** If $n = 1$, move the disc directly from the **Source** peg to the **Destination** peg.
2. **Recursive Steps:**
   - Move top $n-1$ discs from **Source** to **Auxiliary** peg.
   - Move the $n^{\text{th}}$ (largest) disc from **Source** to **Destination** peg.
   - Move the $n-1$ discs from **Auxiliary** to **Destination** peg.

### Mathematical Recurrence Relation
The total number of moves $M(n)$ required for $n$ discs is defined by:
$$M(n) = 2M(n-1) + 1, \quad \text{with } M(1) = 1$$

Solving this recurrence gives the exact closed-form solution:
$$M(n) = 2^n - 1$$

---

## 📊 Experimental Data & Comparisons

| Number of Discs ($n$) | Total Moves Required ($2^n - 1$) | Time Complexity Category |
| :---: | :---: | :---: |
| **1** | $1$ | Very Fast |
| **3** | $7$ | Very Fast |
| **5** | $31$ | Very Fast |
| **10** | $1,023$ | Fast |
| **15** | $32,767$ | Moderate |
| **20** | $1,048,575$ | Noticeable Delay |
| **25** | $33,554,431$ | Slow |
| **30** | $1,073,741,823$ | Extremely Slow |

---

## 📈 Conclusion from the Plot

From the plot of **Total Moves vs. Number of Discs ($n$)**, we conclude that:

1. **Exponential Time Complexity:** The growth curve forms a steep exponential line, proving that the time complexity is **$\mathcal{O}(2^n)$**.
2. **Space Complexity:** The maximum height of the recursive call stack is proportional to $n$, resulting in a space complexity of **$\mathcal{O}(n)$**.
3. **Practical Limit:** Because the required moves double with each additional disc added ($2^n - 1$), the algorithm quickly becomes computationally intractable for values of $n > 30$.

---

## 💻 How to Compile and Run

```bash
# Compile source code
gcc q4.c -o q4.exe

# Execute on Windows
q4.exe

# Execute on Linux / macOS
./q4.exe

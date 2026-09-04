# DAA Lab 6 - Question 2: 0/1 Knapsack Problem using DP

## Problem Statement
Implement the 0/1 Knapsack problem using Dynamic Programming. Given $n$ items with their weights and profits and a knapsack of capacity $W$, determine the maximum profit that can be obtained. Analyze the time and space complexity of your algorithm.

## Approach: Bottom-Up Dynamic Programming (Tabulation)
The 0/1 Knapsack problem involves choosing a subset of items to maximize profit without exceeding the knapsack's weight capacity. A naive recursive approach checks all possible subsets, leading to an exponential time complexity of $O(2^n)$.

To optimize this, the provided C program uses **Dynamic Programming**:
1. We construct a 2D array (table) `dp[n + 1][W + 1]`, where rows represent the items (from $0$ to $n$) and columns represent the knapsack capacities (from $0$ to $W$).
2. The value at `dp[i][w]` stores the maximum profit achievable using the first `i` items with a current weight limit of `w`.
3. We iterate through the table:
   - **Base Case:** If items = $0$ or capacity = $0$, profit is $0$.
   - **If the item fits (`weights[i-1] <= w`):** We take the maximum of either *including* the item (profit of item + max profit of remaining capacity) or *excluding* it (max profit using previous items).
   - **If the item doesn't fit:** We exclude the item and carry over the previous maximum profit.
4. The final answer (maximum profit) is found in the bottom-right cell, `dp[n][W]`.

## Complexity Analysis
- **Time Complexity:** $O(n \times W)$ — The algorithm uses nested loops iterating $n$ times (for items) and $W$ times (for capacities). Checking and updating conditions takes $O(1)$ constant time, resulting in a pseudo-polynomial time complexity.
- **Space Complexity:** $O(n \times W)$ — A 2D array of size $(n + 1) \times (W + 1)$ is allocated to store the subproblem results.

## How to Compile and Run (C Program)

### Prerequisites
Make sure you have a C compiler (like GCC) installed on your system.

### Compilation
Open your terminal and compile the code using the following command:
```bash
gcc q2_knapsack.c -o knapsack

#include <stdio.h>
#include <math.h>
#include <limits.h>

// Function to calculate minimum moves for Reve's Puzzle (4-peg Tower of Hanoi)
long long frameStewart(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    long long min_moves = -1;

    // Find the optimal k that minimizes the number of moves: 2 * T[n - k] + (1 << k) - 1
    // We can iterate through possible values of k from 1 to n-1
    for (int k = 1; k < n; k++) {
        long long current_moves = 2 * frameStewart(n - k) + ((1LL << k) - 1);
        if (min_moves == -1 || current_moves < min_moves) {
            min_moves = current_moves;
        }
    }
    return min_moves;
}

int main() {
    int n = 8; // Given: 8 disks for Reve's puzzle

    printf("--- Reve's Puzzle (4-Peg Tower of Hanoi) ---\n");
    printf("Number of disks (n): %d\n", n);

    long long moves = frameStewart(n);
    printf("Minimum moves required to solve for %d disks: %lld\n", n, moves);

    // Complexity Analysis
    printf("\n--- Complexity Analysis ---\n");
    printf("Time Complexity: O(n^2) with memoization or exponential without, as it checks subproblem partitions for k.\n");
    printf("Space Complexity: O(n) for the recursive call stack depth.\n");

    return 0;
}
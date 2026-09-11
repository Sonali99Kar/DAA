#include <stdio.h>

// Function to calculate the minimum moves to turn off n security switches
long long countSecuritySwitchMoves(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    // Recurrence relation based on the switch constraint rules (Gray code pattern)
    return 2 * countSecuritySwitchMoves(n - 1) + 1;
}

int main() {
    int n;
    printf("Enter the number of security switches (n): ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Please enter a valid non-negative integer.\n");
        return 1;
    }

    long long min_moves = countSecuritySwitchMoves(n);

    printf("\n--- Security Switches Analysis ---\n");
    printf("Number of switches (n): %d\n", n);
    printf("Minimum moves required to turn all switches OFF: %lld\n", min_moves);

    // Complexity Analysis
    printf("\n--- Complexity Analysis ---\n");
    printf("Time Complexity: O(n) or O(2^n) if expanding all individual state steps. Using the direct formula/recursion, it computes in O(n) steps.\n");
    printf("Space Complexity: O(n) due to the recursive stack depth.\n");

    return 0;
}
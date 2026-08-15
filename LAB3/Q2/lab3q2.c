#include <stdio.h>
#include <stdlib.h>

// Global variable to track the number of weighings on the balance scale
int weighing_count = 0;

/**
 * Simulates a balance weighing scale comparing two equal-sized sub-arrays.
 * Returns:
 *  -1 : Left group is lighter
 *   1 : Right group is lighter
 *   0 : Both groups weigh the same
 */
int weigh(float coins[], int left1, int right1, int left2, int right2) {
    weighing_count++;
    float sum1 = 0, sum2 = 0;

    for (int i = left1; i <= right1; i++) sum1 += coins[i];
    for (int i = left2; i <= right2; i++) sum2 += coins[i];

    if (sum1 < sum2) return -1; // Left group is lighter
    if (sum1 > sum2) return 1;  // Right group is lighter
    return 0;                   // Equal weight
}

/**
 * Weighs a single suspect coin against a known standard coin.
 */
int weighSingleAgainstGood(float coins[], int suspectIdx, int goodIdx) {
    weighing_count++;
    if (coins[suspectIdx] < coins[goodIdx]) {
        return -1; // Suspect coin is lighter (defective)
    }
    return 0; // Suspect coin is normal
}

/**
 * Divide and Conquer function to find the defective coin index.
 * Returns the 0-based index of the lighter coin, or -1 if none is lighter.
 */
int findLighterCoin(float coins[], int low, int high, int knownGoodIdx) {
    int len = high - low + 1;

    // Base Case 1: No elements left
    if (len <= 0) return -1;

    // Base Case 2: Only 1 suspect coin left
    if (len == 1) {
        if (knownGoodIdx != -1) {
            int result = weighSingleAgainstGood(coins, low, knownGoodIdx);
            return (result == -1) ? low : -1;
        }
        // If no known good coin index yet, return -1 (or handle at root level)
        return -1;
    }

    int k = len / 2; // Size of each of the two groups
    int left1 = low, right1 = low + k - 1;
    int left2 = low + k, right2 = low + 2 * k - 1;

    // Weigh Group 1 against Group 2
    int outcome = weigh(coins, left1, right1, left2, right2);

    if (outcome == -1) {
        // Defective coin is in Group 1
        return findLighterCoin(coins, left1, right1, left2);
    } 
    else if (outcome == 1) {
        // Defective coin is in Group 2
        return findLighterCoin(coins, left2, right2, left1);
    } 
    else {
        // Both groups are equal! Group 1 & 2 contain only genuine coins.
        // Leftover coin (if len is odd) is at index 'high'
        if (len % 2 != 0) {
            int result = weighSingleAgainstGood(coins, high, left1);
            return (result == -1) ? high : -1;
        }
        return -1; // Even number of coins and all balanced => No defective coin
    }
}

int main() {
    int n = 15;
    float standardWeight = 10.0;
    float defectiveWeight = 9.2; // Lighter weight

    float coins[15];

    // Case A: Defective coin present at index 7
    for (int i = 0; i < n; i++) coins[i] = standardWeight;
    int actual_defective = 7;
    coins[actual_defective] = defectiveWeight;

    weighing_count = 0;
    int found_idx = findLighterCoin(coins, 0, n - 1, -1);

    printf("--- Test Case A (Defective Coin Present) ---\n");
    printf("Total Coins: %d\n", n);
    if (found_idx != -1)
        printf("Defective coin found at Index: %d (Weight: %.1f)\n", found_idx, coins[found_idx]);
    else
        printf("No defective coin found.\n");
    printf("Total Balance Scale Weighings Used: %d\n\n", weighing_count);

    // Case B: No defective coin present
    for (int i = 0; i < n; i++) coins[i] = standardWeight;

    weighing_count = 0;
    found_idx = findLighterCoin(coins, 0, n - 1, -1);

    printf("--- Test Case B (No Defective Coin) ---\n");
    printf("Total Coins: %d\n", n);
    if (found_idx != -1)
        printf("Defective coin found at Index: %d\n", found_idx);
    else
        printf("All coins are perfect! No defective coin detected.\n");
    printf("Total Balance Scale Weighings Used: %d\n", weighing_count);

    return 0;
}

#include <stdio.h>

// Helper variable to count moves
int move_count = 0;

// Function to solve Towers of Hanoi
void hanoi(int n, char source, char target, char aux) {
    // Base case: If no discs, do nothing
    if (n == 0) {
        return;
    }

    // Step 1: Move (n-1) discs from source to aux
    hanoi(n - 1, source, aux, target);

    // Step 2: Move the remaining disc to target
    move_count++;

    // Step 3: Move (n-1) discs from aux to target
    hanoi(n - 1, aux, target, source);
}

int main() {
    printf("Discs\tTotal Moves\n");
    printf("-------------------\n");

    // Loop through 1 to 5 discs
    for (int n = 1; n <= 5; n++) {
        move_count = 0; // Reset counter for each test
        
        hanoi(n, 'A', 'C', 'B'); // 'A' = Start, 'C' = Destination, 'B' = Helper
        
        printf("%d\t%d\n", n, move_count);
    }

    return 0;
}
#include <stdio.h>

int move_count = 0;

void hanoi(int n, char source, char target, char aux) {
    if (n == 0) return;
    hanoi(n - 1, source, aux, target);
    move_count++;
    hanoi(n - 1, aux, target, source);
}

int main() {
    printf("Discs\tTotal Moves\tTheoretical (2^n - 1)\n");
    printf("---------------------------------------------\n");
    for (int n = 1; n <= 15; n++) {
        move_count = 0;
        hanoi(n, 'A', 'C', 'B');
        printf("%d\t%d\t\t%d\n", n, move_count, (1 << n) - 1);
    }
    return 0;
}

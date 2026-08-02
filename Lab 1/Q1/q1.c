#include <stdio.h>
#include <math.h>

void print_function_values(double n) {
    printf("====================================================\n");
    printf("          FUNCTION VALUES AT n = %.0e\n", n);
    printf("====================================================\n");
    printf("1                 : %e\n", 1.0);
    printf("log2(n)           : %f\n", log2(n));
    printf("12 * sqrt(n)      : %e\n", 12.0 * sqrt(n));
    printf("50 * n^0.5        : %e\n", 50.0 * sqrt(n));
    printf("n^0.51            : %e\n", pow(n, 0.51));
    printf("n                 : %e\n", n);
    printf("n * log2(n)       : %e\n", n * log2(n));
    printf("100n^2 + 6n       : %e\n", 100.0 * n * n + 6.0 * n);
    printf("n^2 - 324         : %e\n", n * n - 324.0);
    printf("2 * n^3           : %e\n", 2.0 * pow(n, 3));

    // Exponential Functions with overflow checks
    if (n * log2(3) < 1000) {
        printf("3^n               : %e\n", pow(3.0, n));
    } else {
        printf("3^n               : OVERFLOW (> 1e308)\n");
    }

    if (32.0 * n * log2(2) < 1000) {
        printf("2^(32n)           : %e\n", pow(2.0, 32.0 * n));
    } else {
        printf("2^(32n)           : OVERFLOW (> 1e308)\n");
    }
}

int main() {
    print_function_values(1000.0);        // n = 10^3
    print_function_values(100000.0);      // n = 10^5
    print_function_values(1000000000.0);  // n = 10^9
    return 0;
}

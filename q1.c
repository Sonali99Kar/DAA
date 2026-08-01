#include <stdio.h>
#include <math.h>

// Helper to safely evaluate functions that grow extremely fast
void print_function_values(double n) {
    printf("====================================================\n");
    printf("          FUNCTION VALUES AT n = %.0e\n", n);
    printf("====================================================\n");

    printf("1 / n             : %e\n", 1.0 / n);
    printf("log2(n)           : %f\n", log2(n));
    printf("12 * sqrt(n)      : %e\n", 12.0 * sqrt(n));
    printf("50 * n^0.5        : %e\n", 50.0 * sqrt(n));
    printf("n^0.51            : %e\n", pow(n, 0.51));
    printf("2^32 * n          : %e\n", pow(2, 32) * n);
    printf("n * log2(n)       : %e\n", n * log2(n));
    printf("n^2 - 324         : %e\n", n * n - 324.0);
    printf("100n^2 + 6n       : %e\n", 100.0 * n * n + 6.0 * n);
    printf("2 * n^3           : %e\n", 2.0 * pow(n, 3));
    
    // Growth rates that quickly overflow double capacity (~1e308)
    if (log2(n) * log2(n) * log2(2) < 300) {
        printf("n^(log2 n)        : %e\n", pow(n, log2(n)));
    } else {
        printf("n^(log2 n)        : OVERFLOW (> 1e308)\n");
    }

    if (n * log2(3) < 1000) {
        printf("3^n               : %e\n", pow(3.0, n));
    } else {
        printf("3^n               : OVERFLOW (> 1e308)\n");
    }
}

int main() {
    // Testing with moderately large and extremely large values of n
    print_function_values(1000.0);        // n = 10^3
    print_function_values(100000.0);      // n = 10^5
    print_function_values(1000000000.0);  // n = 10^9

    return 0;
}
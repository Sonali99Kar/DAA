#include <stdio.h>
#include <stdlib.h>

// Function to compute the next Collatz term with overflow protection
long long collatzNext(long long n) {
    if (n % 2 == 0) {
        return n / 2;
    } else {
        return 3 * n + 1;
    }
}

// Structure to hold trajectory statistics
typedef struct {
    long long start_value;
    long long steps;
    long long peak_value;
} CollatzStats;

// Function to analyze a single number's trajectory
CollatzStats analyzeTrajectory(long long n) {
    CollatzStats stats;
    stats.start_value = n;
    stats.steps = 0;
    stats.peak_value = n;
    
    long long current = n;
    while (current > 1) {
        if (current > stats.peak_value) {
            stats.peak_value = current;
        }
        current = collatzNext(current);
        stats.steps++;
    }
    
    return stats;
}

// Function to analyze trajectories across an interval [a, b]
void analyzeInterval(long long a, long long b) {
    if (a > b) {
        long long temp = a;
        a = b;
        b = temp;
    }
    
    long long max_steps = -1;
    long long max_steps_val = -1;
    long long global_peak = -1;
    long long peak_val = -1;
    
    printf("\n--- Interval Analysis [%lld, %lld] ---\n", a, b);
    
    for (long long i = a; i <= b; i++) {
        if (i <= 0) continue;
        CollatzStats stats = analyzeTrajectory(i);
        
        if (stats.steps > max_steps) {
            max_steps = stats.steps;
            max_steps_val = stats.start_value;
        }
        if (stats.peak_value > global_peak) {
            global_peak = stats.peak_value;
            peak_val = stats.start_value;
        }
    }
    
    printf("Number with longest trajectory: %lld (%lld steps)\n", max_steps_val, max_steps);
    printf("Number with highest peak value: %lld (Peak: %lld)\n", peak_val, global_peak);
}

int main() {
    long long single_n;
    long long a, b;
    
    // 1. Analyze a single user-provided starting value
    printf("Enter a starting value n for Collatz analysis: ");
    if (scanf("%lld", &single_n) != 1 || single_n <= 0) {
        printf("Invalid input for starting value.\n");
        return 1;
    }
    
    CollatzStats single_stats = analyzeTrajectory(single_n);
    printf("\n--- Single Value Results ---\n");
    printf("Starting Value: %lld\n", single_stats.start_value);
    printf("Total Steps to Reach 1: %lld\n", single_stats.steps);
    printf("Peak Value Reached: %lld\n", single_stats.peak_value);
    
    // 2. Analyze across an interval [a, b]
    printf("\nEnter interval bounds (a and b) for range analysis:\n");
    printf("Enter a: ");
    scanf("%lld", &a);
    printf("Enter b: ");
    scanf("%lld", &b);
    
    analyzeInterval(a, b);
    
    return 0;
}
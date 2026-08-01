#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to simulate coin tosses with a specified probability of getting HEAD
void simulate_coin_toss(int trials, double bias, const char* coin_type) {
    int heads = 0;
    int tails = 0;

    for (int i = 0; i < trials; i++) {
        // Generate a random double precision float between 0.0 and 1.0
        double r = (double)rand() / RAND_MAX;
        
        if (r < bias) {
            heads++;
        } else {
            tails++;
        }
    }

    double prob_heads = (double)heads / trials;
    double prob_tails = (double)tails / trials;

    printf("--- %s Simulation ---\n", coin_type);
    printf("Total Trials      : %d\n", trials);
    printf("Expected P(HEAD)   : %.2f\n", bias);
    printf("Simulated P(HEAD)  : %.4f (%d Heads)\n", prob_heads, heads);
    printf("Simulated P(TAIL)  : %.4f (%d Tails)\n\n", prob_tails, tails);
}

int main() {
    // Seed the random number generator
    srand((unsigned int)time(NULL));

    // Number of experiments / tosses
    int trials = 100000;

    // 1. Fair Coin Simulation (P(HEAD) = 0.50)
    simulate_coin_toss(trials, 0.50, "Fair Coin");

    // 2. Biased Coin Simulation (P(HEAD) = 0.75)
    simulate_coin_toss(trials, 0.75, "Biased Coin (75% Heads)");

    // 3. Biased Coin Simulation (P(HEAD) = 0.20)
    simulate_coin_toss(trials, 0.20, "Biased Coin (20% Heads)");

    return 0;
}
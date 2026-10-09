#include <stdio.h>
#include <stdlib.h>

struct Item {
    int id;
    double value;
    double weight;
    double decay_rate;
    double priority;
};

// Comparison function to sort items in descending order of priority
int compare(const void *a, const void *b) {
    struct Item *item1 = (struct Item *)a;
    struct Item *item2 = (struct Item *)b;
    if (item2->priority > item1->priority) return 1;
    else if (item2->priority < item1->priority) return -1;
    return 0;
}

void fractionalKnapsackDeterioration(struct Item items[], int n, double capacity) {
    // Priority based on value density relative to its decay rate: (v_i / w_i) / lambda_i
    for (int i = 0; i < n; i++) {
        items[i].priority = (items[i].value / items[i].weight) / items[i].decay_rate;
    }

    qsort(items, n, sizeof(struct Item), compare);

    double current_weight = 0.0;
    double current_time = 0.0;
    double total_value = 0.0;

    printf("\n--- Optimal Schedule & Fractional Choices ---\n");
    for (int i = 0; i < n; i++) {
        if (current_weight >= capacity) break;

        double weight_to_take = 0.0;
        if (current_weight + items[i].weight <= capacity) {
            weight_to_take = items[i].weight;
        } else {
            weight_to_take = capacity - current_weight;
        }

        // Effective value density at the midpoint of consumption interval [current_time, current_time + weight_to_take]
        double base_density = items[i].value / items[i].weight;
        double avg_time = current_time + (weight_to_take / 2.0);
        double effective_density = base_density - (items[i].decay_rate * avg_time);
        
        if (effective_density < 0) effective_density = 0;

        double earned_value = weight_to_take * effective_density;
        total_value += earned_value;

        printf("Item %d: Took weight = %.2f (out of %.2f), Start time t = %.2f, Earned Value = %.2f\n",
               items[i].id, weight_to_take, items[i].weight, current_time, earned_value);

        current_time += weight_to_take;
        current_weight += weight_to_take;
    }

    printf("\nMaximum Total Value Accumulated = %.2f\n", total_value);
}

int main() {
    int n;
    double capacity;

    printf("Enter number of items: ");
    if (scanf("%d", &n) != 1) return 1;

    printf("Enter knapsack capacity: ");
    if (scanf("%lf", &capacity) != 1) return 1;

    struct Item *items = (struct Item *)malloc(n * sizeof(struct Item));

    printf("Enter base value, weight, and decay rate for each item:\n");
    for (int i = 0; i < n; i++) {
        items[i].id = i + 1;
        printf("Item %d (Value Weight Decay): ", i + 1);
        scanf("%lf %lf %lf", &items[i].value, &items[i].weight, &items[i].decay_rate);
    }

    fractionalKnapsackDeterioration(items, n, capacity);

    free(items);
    return 0;
}

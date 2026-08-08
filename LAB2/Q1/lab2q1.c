#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Node structure for Singly Linked List
typedef struct SNode {
    int key;
    struct SNode *next;
} SNode;

// Node structure for Doubly Linked List
typedef struct DNode {
    int key;
    struct DNode *next, *prev;
} DNode;

// Memory cleanup helpers
void free_slist(SNode *head) {
    while (head) { SNode *t = head; head = head->next; free(t); }
}

void free_dlist(DNode *head) {
    while (head) { DNode *t = head; head = head->next; free(t); }
}

int main() {
    FILE *f_u_arr = fopen("ds_unsorted_array.txt", "w");
    FILE *f_s_arr = fopen("ds_sorted_array.txt", "w");
    FILE *f_s_u_list = fopen("ds_singly_unsorted.txt", "w");
    FILE *f_s_s_list = fopen("ds_singly_sorted.txt", "w");
    FILE *f_d_u_list = fopen("ds_doubly_unsorted.txt", "w");
    FILE *f_d_s_list = fopen("ds_doubly_sorted.txt", "w");

    if (!f_u_arr || !f_s_arr || !f_s_u_list || !f_s_s_list || !f_d_u_list || !f_d_s_list) {
        printf("Error creating data files!\n");
        return 1;
    }

    printf("Benchmarking 6 Data Structures for 7 Primary Operations...\n");

    for (int n = 2000; n <= 20000; n += 2000) {
        clock_t start;
        int target = -1; // Unmatched target forces worst-case scanning

        // ==========================================
        // 1. UNSORTED ARRAY
        // ==========================================
        int *u_arr = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) u_arr[i] = i * 2;

        // Search: O(n)
        start = clock();
        for (int t = 0; t < 200; t++) {
            for (int i = 0; i < n; i++) if (u_arr[i] == target) break;
        }
        double u_arr_search = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        // Insert: O(1)
        start = clock();
        for (int t = 0; t < 200; t++) u_arr[n - 1] = 999;
        double u_arr_insert = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        // Delete: O(1)
        start = clock();
        for (int t = 0; t < 200; t++) u_arr[0] = u_arr[n - 1];
        double u_arr_delete = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        // Max / Min: O(n)
        start = clock();
        for (int t = 0; t < 200; t++) {
            int mx = u_arr[0];
            for (int i = 1; i < n; i++) if (u_arr[i] > mx) mx = u_arr[i];
        }
        double u_arr_minmax = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        // Predecessor / Successor: O(n)
        start = clock();
        for (int t = 0; t < 200; t++) {
            int pred = -1;
            for (int i = 0; i < n; i++) if (u_arr[i] < u_arr[0] && u_arr[i] > pred) pred = u_arr[i];
        }
        double u_arr_predsucc = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        fprintf(f_u_arr, "%d %f %f %f %f %f %f %f\n", 
                n, u_arr_search, u_arr_insert, u_arr_delete, u_arr_minmax, u_arr_minmax, u_arr_predsucc, u_arr_predsucc);
        free(u_arr);


        // ==========================================
        // 2. SORTED ARRAY
        // ==========================================
        int *s_arr = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) s_arr[i] = i * 2;

        // Search: O(log n)
        start = clock();
        for (int t = 0; t < 5000; t++) {
            int l = 0, r = n - 1;
            while (l <= r) {
                int m = l + (r - l) / 2;
                if (s_arr[m] == target) break;
                if (s_arr[m] < target) l = m + 1; else r = m - 1;
            }
        }
        double s_arr_search = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        // Insert / Delete: O(n) due to element shifting
        start = clock();
        for (int t = 0; t < 200; t++) {
            for (int i = n - 1; i > 0; i--) s_arr[i] = s_arr[i - 1];
        }
        double s_arr_shift = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        // Max / Min / Pred / Succ: O(1) direct indexing
        start = clock();
        for (int t = 0; t < 5000; t++) {
            int min = s_arr[0], max = s_arr[n - 1];
            int pred = s_arr[n / 2 - 1], succ = s_arr[n / 2 + 1];
        }
        double s_arr_constant = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        fprintf(f_s_arr, "%d %f %f %f %f %f %f %f\n", 
                n, s_arr_search, s_arr_shift, s_arr_shift, s_arr_constant, s_arr_constant, s_arr_constant, s_arr_constant);
        free(s_arr);


        // ==========================================
        // 3. SINGLY LINKED LIST (UNSORTED)
        // ==========================================
        SNode *s_u_head = NULL;
        for (int i = 0; i < n; i++) {
            SNode *nd = (SNode *)malloc(sizeof(SNode));
            nd->key = i * 2; nd->next = s_u_head; s_u_head = nd;
        }

        // Search / Delete / Min / Max / Pred / Succ: O(n)
        start = clock();
        for (int t = 0; t < 200; t++) {
            SNode *c = s_u_head;
            while (c) { if (c->key == target) break; c = c->next; }
        }
        double s_u_scan = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        // Insert at head: O(1)
        start = clock();
        for (int t = 0; t < 5000; t++) {
            SNode *temp = (SNode *)malloc(sizeof(SNode));
            temp->next = s_u_head; free(temp);
        }
        double s_u_insert = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        fprintf(f_s_u_list, "%d %f %f %f %f %f %f %f\n", 
                n, s_u_scan, s_u_insert, s_u_scan, s_u_scan, s_u_scan, s_u_scan, s_u_scan);
        free_slist(s_u_head);


        // ==========================================
        // 4. SINGLY LINKED LIST (SORTED)
        // ==========================================
        SNode *s_s_head = NULL, *s_s_tail = NULL;
        for (int i = 0; i < n; i++) {
            SNode *nd = (SNode *)malloc(sizeof(SNode));
            nd->key = i * 2; nd->next = NULL;
            if (!s_s_head) s_s_head = s_s_tail = nd;
            else { s_s_tail->next = nd; s_s_tail = nd; }
        }

        // Search / Insert / Delete / Predecessor: O(n)
        start = clock();
        for (int t = 0; t < 200; t++) {
            SNode *c = s_s_head;
            while (c) { if (c->key == target) break; c = c->next; }
        }
        double s_s_scan = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        // Min / Max / Successor: O(1)
        start = clock();
        for (int t = 0; t < 5000; t++) {
            int min = s_s_head->key, max = s_s_tail->key;
            SNode *succ = s_s_head->next;
        }
        double s_s_constant = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        fprintf(f_s_s_list, "%d %f %f %f %f %f %f %f\n", 
                n, s_s_scan, s_s_scan, s_s_scan, s_s_constant, s_s_constant, s_s_scan, s_s_constant);
        free_slist(s_s_head);


        // ==========================================
        // 5. DOUBLY LINKED LIST (UNSORTED)
        // ==========================================
        DNode *d_u_head = NULL;
        for (int i = 0; i < n; i++) {
            DNode *nd = (DNode *)malloc(sizeof(DNode));
            nd->key = i * 2; nd->next = d_u_head; nd->prev = NULL;
            if (d_u_head) d_u_head->prev = nd;
            d_u_head = nd;
        }

        // Search / Min / Max / Pred / Succ: O(n)
        start = clock();
        for (int t = 0; t < 200; t++) {
            DNode *c = d_u_head;
            while (c) { if (c->key == target) break; c = c->next; }
        }
        double d_u_scan = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        // Insert / Delete: O(1) pointer updates
        start = clock();
        for (int t = 0; t < 5000; t++) {
            DNode *temp = d_u_head;
            if (temp->next) temp->next->prev = temp->prev;
        }
        double d_u_constant = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        fprintf(f_d_u_list, "%d %f %f %f %f %f %f %f\n", 
                n, d_u_scan, d_u_constant, d_u_constant, d_u_scan, d_u_scan, d_u_scan, d_u_scan);
        free_dlist(d_u_head);


        // ==========================================
        // 6. DOUBLY LINKED LIST (SORTED)
        // ==========================================
        DNode *d_s_head = NULL, *d_s_tail = NULL;
        for (int i = 0; i < n; i++) {
            DNode *nd = (DNode *)malloc(sizeof(DNode));
            nd->key = i * 2; nd->next = NULL; nd->prev = d_s_tail;
            if (!d_s_head) d_s_head = d_s_tail = nd;
            else { d_s_tail->next = nd; d_s_tail = nd; }
        }

        // Search / Insert: O(n)
        start = clock();
        for (int t = 0; t < 200; t++) {
            DNode *c = d_s_head;
            while (c) { if (c->key == target) break; c = c->next; }
        }
        double d_s_scan = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        // Delete / Min / Max / Pred / Succ: O(1)
        start = clock();
        for (int t = 0; t < 5000; t++) {
            int min = d_s_head->key, max = d_s_tail->key;
            DNode *pred = d_s_head->next ? d_s_head->next->prev : NULL;
            DNode *succ = d_s_head->next;
        }
        double d_s_constant = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        fprintf(f_d_s_list, "%d %f %f %f %f %f %f %f\n", 
                n, d_s_scan, d_s_scan, d_s_constant, d_s_constant, d_s_constant, d_s_constant, d_s_constant);
        free_dlist(d_s_head);
    }

    fclose(f_u_arr); fclose(f_s_arr); fclose(f_s_u_list);
    fclose(f_s_s_list); fclose(f_d_u_list); fclose(f_d_s_list);

    printf("Data collection completed. Plotting 6 separate graphs...\n");

    // Launch Gnuplot script to plot 6 individual graphs
    FILE *gnuplot = popen("gnuplot -persistent", "w");
    if (gnuplot) {
        // Macro setting for operation colors
        const char *plot_cmd = 
            "set xlabel 'Input Size (n)'; set ylabel 'Time (s)'; set grid; "
            "plot file using 1:2 with linespoints lc rgb '#FF0000' lw 2 title 'Search', "
            "     file using 1:3 with linespoints lc rgb '#00FF00' lw 2 title 'Insert', "
            "     file using 1:4 with linespoints lc rgb '#0000FF' lw 2 title 'Delete', "
            "     file using 1:5 with linespoints lc rgb '#FFA500' lw 2 title 'Maximum', "
            "     file using 1:6 with linespoints lc rgb '#800080' lw 2 title 'Minimum', "
            "     file using 1:7 with linespoints lc rgb '#00FFFF' lw 2 title 'Predecessor', "
            "     file using 1:8 with linespoints lc rgb '#FF00FF' lw 2 title 'Successor'\n";

        // Graph 1
        fprintf(gnuplot, "set term qt 0 title 'Graph 1: Unsorted Array'\n");
        fprintf(gnuplot, "set title '1. Unsorted Array Operations'\n");
        fprintf(gnuplot, "file = 'ds_unsorted_array.txt'\n");
        fprintf(gnuplot, "%s", plot_cmd);

        // Graph 2
        fprintf(gnuplot, "set term qt 1 title 'Graph 2: Sorted Array'\n");
        fprintf(gnuplot, "set title '2. Sorted Array Operations'\n");
        fprintf(gnuplot, "file = 'ds_sorted_array.txt'\n");
        fprintf(gnuplot, "%s", plot_cmd);

        // Graph 3
        fprintf(gnuplot, "set term qt 2 title 'Graph 3: Singly Linked Unsorted List'\n");
        fprintf(gnuplot, "set title '3. Singly Linked Unsorted List Operations'\n");
        fprintf(gnuplot, "file = 'ds_singly_unsorted.txt'\n");
        fprintf(gnuplot, "%s", plot_cmd);

        // Graph 4
        fprintf(gnuplot, "set term qt 3 title 'Graph 4: Singly Linked Sorted List'\n");
        fprintf(gnuplot, "set title '4. Singly Linked Sorted List Operations'\n");
        fprintf(gnuplot, "file = 'ds_singly_sorted.txt'\n");
        fprintf(gnuplot, "%s", plot_cmd);

        // Graph 5
        fprintf(gnuplot, "set term qt 4 title 'Graph 5: Doubly Linked Unsorted List'\n");
        fprintf(gnuplot, "set title '5. Doubly Linked Unsorted List Operations'\n");
        fprintf(gnuplot, "file = 'ds_doubly_unsorted.txt'\n");
        fprintf(gnuplot, "%s", plot_cmd);

        // Graph 6
        fprintf(gnuplot, "set term qt 5 title 'Graph 6: Doubly Linked Sorted List'\n");
        fprintf(gnuplot, "set title '6. Doubly Linked Sorted List Operations'\n");
        fprintf(gnuplot, "file = 'ds_doubly_sorted.txt'\n");
        fprintf(gnuplot, "%s", plot_cmd);

        pclose(gnuplot);
    }

    return 0;
}

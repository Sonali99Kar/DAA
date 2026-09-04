#include <stdio.h>
#include <string.h>

// Helper function to find the maximum of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to find and print the LCS
void findLCS(char X[], char Y[], int m, int n) {
   
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0; // Base case: empty string
            } else if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1; // Characters match
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); // Characters don't match
            }
        }
    }

    int length = dp[m][n];
    printf("Length of the Longest Common Subsequence: %d\n", length);

    char lcs[length + 1];
    lcs[length] = '\0'; // Null-terminate the string

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[length - 1] = X[i - 1]; 
            i--;
            j--;
            length--; 
        } 
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    printf("The Longest Common Subsequence is: %s\n", lcs);
}

int main() {
    // Example strings
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";
    
    int m = strlen(X);
    int n = strlen(Y);
    
    printf("String 1: %s\n", X);
    printf("String 2: %s\n", Y);
    printf("------------------------------------\n");
    
    findLCS(X, Y, m, n);
    
    return 0;
}

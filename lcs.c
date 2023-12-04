#include <stdlib.h>
#include <stdio.h>

#include "reverse.h"
#include "string_algo.h"

#define GET(C,i,j) C[(i) * (n + 1) + (j)]

// A non-recursive version of the LCS backtracking function on Wikipedia
void lcs_backtrack(const int *C, const char *X, const char *Y, int m, int n, char *lcs) {
  int i = m;
  int j = n;
  int pos = 0;
  while (i != 0 && j != 0) {
    if (X[i-1] == Y[j-1]) {
        lcs[pos++] = X[i-1];
        i--;
        j--;
    } else if (GET(C,i,j-1) > GET(C,i-1,j)) {
        j--;
    } else {
        i--;
    }
  }
  reverse(lcs, pos);
  lcs[pos] = '\0';
}

/**
* Returns the length of the Longest Common Subsequence (LCS) of two strings.
* 
* @param X the first string
* @param Y the second string
* @param m the length of the first string
* @param n the length of the second string
* @param lcs the longest common subsequence of X and Y
*
* @return the length of the LCS
*/
int lcs_string(const char* X, const char* Y, int m, int n, char* lcs) {
    //int C[m+1][n+1];
    int *C = calloc((m + 1) * (n + 1), sizeof(int));
    for (int i=0; i<=m; i++) {
        for (int j=0; j<=n; j++) {
            if (i==0 || j==0) {
                GET(C,i,j) = 0;
            } else if (X[i-1] == Y[j-1]) {
                GET(C,i,j) = GET(C, i-1, j-1) + 1;
            } else {
                GET(C,i,j) = GET(C, i, j-1) > GET(C, i-1, j) ? GET(C, i, j-1) : GET(C, i-1, j);
            }
        }
    }
    int out = GET(C, m, n);
    lcs_backtrack(C, X, Y, m, n, lcs);
    free(C);
    return out;
}

#undef GET

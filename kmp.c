#include <stdio.h>
#include <string.h>

#include "string_algo.h"

/*
   input:
       an array of characters, W (the word to be analyzed)
   output:
       an array of integers, T (the table to be filled)
*/
int kmp_table(const char *W, int *T) {
  int pos = 1; // the current position we are computing in T
  int cnd = 0; // the zero-based index in W of the next character of the current
               // candidate substring
  T[0] = -1;
  while (pos < strlen(W)) {
    if (W[pos] == W[cnd]) {
      T[pos] = T[cnd];
    } else {
      while (cnd >= 0 && W[pos] != W[cnd]) {
        cnd = T[cnd];
      }
    }
    pos++;
    cnd++;
  }
  T[pos] = cnd; // only needed when all word occurrences are searched
  return 0;
}

/*
    input:
        an array of characters, S (the text to be searched)
        an array of characters, W (the word sought)
    output:
        an array of integers, P (positions in S at which W is found)
        an integer, nP (number of positions)
*/
void kmp_search(const char *S, const char *W, const int* T, int *P, int *nP) {
  int j = 0;  // the position of the current character in S)
  int k = 0;  // the position of the current character in W)
  //int T[256]; // the table, computed elsewhere)
  (*nP) = 0;
  while (j < strlen(S)) {
    if (W[k] == S[j]) {
      j++;
      k++;
      if (k == strlen(W)) {
        // occurrence found, if only first occurrence is needed, m ← j - k  may
        // be returned here
        P[*nP] = j - k;
        (*nP)++;
        k = T[k];
        // T[length(W)] can't be -1
      }
    } else {
      k = T[k];
      if (k < 0) {
        j++;
        k++;
      }
    }
  }
}


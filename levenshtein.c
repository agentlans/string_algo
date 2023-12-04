#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string_algo.h"
#include "reverse.h"

// Maximum of two integers
int max2(int a, int b) {
  if (a > b) {
    return a;
  } else {
    return b;
  }
}

// Minimum of two integers
int min2(int a, int b) {
  if (a < b) {
    return a;
  } else {
    return b;
  }
}

// Minimum of three integers
int min3(int a, int b, int c) {
  if (a <= b && a <= c)
    return a;
  else if (b <= a && b <= c)
    return b;
  return c;
}

// Adaptation of code from https://en.wikipedia.org/wiki/Levenshtein_distance

#define GET(i, j) d[(i) * (n + 1) + (j)]

/**
 * Aligns strings s and t.
 *
 * @param s the first string to align
 * @param t the second string to align
 * @param d the matrix from the Levenshtein distance comparison
 * @param m the length of the first string
 * @param n the length of the second string
 * @param aln1 the output alignment of the first string
 * @param aln2 the output alignment of the second string
 */
void lev_backtrack(const char *s, const char *t, const int *d, int m, int n,
               char *aln1, char *aln2) {
  int i = m, j = n;
  int pos1 = 0, pos2 = 0;
  while (i >= 1 || j >= 1) {
    int dij = GET(i, j);
    if (i >= 1 && dij == GET(i - 1, j) + 1) {
      // deleted
      aln1[pos1] = s[i - 1];
      aln2[pos2] = '-';
      i--;
    } else if (j >= 1 && dij == GET(i, j - 1) + 1) {
      // inserted
      aln1[pos1] = '-';
      aln2[pos2] = t[j - 1];
      j--;
    } else {
      // same or substitute
      aln1[pos1] = s[i - 1];
      aln2[pos2] = t[j - 1];
      i--;
      j--;
    }
    pos1++;
    pos2++;
  }
  reverse(aln1, pos1);
  reverse(aln2, pos2);
  // Trailing null
  aln1[pos1] = '\0';
  aln2[pos2] = '\0';
}

/**
 * Aligns strings s and t by Levenshtein distance.
 *
 * @param s the first string to align
 * @param t the second string to align
 * @param m length of s
 * @param n length of t
 * @param aln1 the alignment of s with gap characters inserted
 * @param aln2 the alignment of t with gap characters inserted
 *
 * @return an integer representing the Levenshtein distance between s and t
 */
int lev_alignment(char *s, char *t, int m, int n, char *aln1, char *aln2) {
  // Initialize matrix to zero
  int *d = calloc((m + 1) * (n + 1), sizeof(int));

  // Source prefixes can be transformed into empty string by
  // dropping all characters.
  for (int i = 0; i <= m; i++) {
    GET(i, 0) = i;
  }

  // Target prefixes can be reached from empty source prefix
  // by inserting every character
  for (int j = 0; j <= n; j++) {
    GET(0, j) = j;
  }

  // Compute distances
  for (int j = 1; j <= n; j++) {
    for (int i = 1; i <= m; i++) {
      int substitutionCost;
      if (s[i - 1] == t[j - 1]) {
        substitutionCost = 0;
      } else {
        substitutionCost = 1;
      }

      GET(i, j) = min3(GET(i - 1, j) + 1,                     // deletion
                       GET(i, j - 1) + 1,                     // insertion
                       GET(i - 1, j - 1) + substitutionCost); // substitution
    }
  }
  // Reconstruct the alignment
  lev_backtrack(s, t, (int *)d, m, n, aln1, aln2);
  int out = GET(m, n);
  free(d);
  return out;
}

#undef GET

/**
 * Computes the Levenshtein distance between two strings.
 *
 * @param s the first string to align
 * @param t the second string to align
 * @param m length of s
 * @param n length of t
 *
 * @return an integer representing the Levenshtein distance between s and t
 */
int lev_distance(const char *s, const char *t, int m, int n) {
  /* create two work vectors of integer distances */
  int wrk_size = max2(m, n) + 1;
  int v0[wrk_size];
  int v1[wrk_size];

  // initialize v0 (the previous row of distances)
  for (int i = 0; i <= n; i++) {
    v0[i] = i;
  }

  for (int i = 0; i < m; i++) {
    // calculate v1 (current row distances) from the previous row v0

    v1[0] = i + 1;

    for (int j = 0; j < n; j++) {
      // calculating costs for A[i + 1][j + 1]
      int deletionCost = v0[j + 1] + 1;
      int insertionCost = v1[j] + 1;
      int substitutionCost;
      if (s[i] == t[j]) {
        substitutionCost = v0[j];
      } else {
        substitutionCost = v0[j] + 1;
      }

      v1[j + 1] = min3(deletionCost, insertionCost, substitutionCost);
    }

    // copy v1 (current row) to v0 (previous row) for next iteration
    memmove(v0, v1, (n + 1) * sizeof(int));
  }
  // after the last swap, the results of v1 are now in v0
  return v0[n];
}


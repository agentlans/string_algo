#ifndef _STRINGALGO
#define _STRINGALGO

int lcs_string(const char* X, const char* Y, int m, int n, char* lcs);
int lev_alignment(char *s, char *t, int m, int n, char *aln1, char *aln2);
int lev_distance(const char *s, const char *t, int m, int n);
int kmp_table(const char *W, int *T);
void kmp_search(const char *S, const char *W, const int* T, int *P, int *nP);

#endif

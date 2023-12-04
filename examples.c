#include <stdio.h>
#include <string.h>

#include "string_algo.h"

int lev_main() {
  char s1[] = "Saturday";
  char s2[] = "Sunday";
  char aln1[] = "                      ";
  char aln2[] = "                      ";
  printf("%d\n", lev_alignment(s1, s2, strlen(s1), strlen(s2), aln1, aln2));
  printf("%d\n", lev_distance(s1, s2, strlen(s1), strlen(s2)));
  printf("%s\n%s\n", aln1, aln2);
}

int kmp_main() {
	int T[100];
	kmp_table("needle", T);
	int P[100];
	int nP;
	kmp_search("123490xcneedlexcb9wsneedlexbb", "needle", T, P, &nP);
	for (int i = 0; i < nP; ++i)
		printf("%d ", P[i]);
}

int lcs_main() {
    int m = 7;
    int n = 5;
    char lcs[] = "###########";
    printf("%d\n", lcs_string("ABCDGHI", "AEDFH", m, n, lcs)); // Output: 3
    printf("%s\n", lcs);
    return 0;
}

int main() {
	lev_main();
	kmp_main();
	lcs_main();
}

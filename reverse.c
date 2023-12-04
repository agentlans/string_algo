#include "reverse.h"

// Reverses a string in-place
// len: length of the string
void reverse(char *s, size_t len) {
  char *p1 = s;
  char *p2 = s + len - 1;
  while (p2 > p1) {
    // Swap p1 and p2
    char temp = *p2;
    *p2 = *p1;
    *p1 = temp;
    p1++;
    p2--;
  }
}

#include <stdio.h>

int main(void)

{ int c;  int charCount = 0;  c = getchar();  while (c != EOF) { charCount++; c = getchar(); }   printf("%d\n", charCount);  return 0;}


#include <stdio.h>

/* 2 conditions to be able to use recursion:
    i) problem expressible in a recursive form
    ii) a end condition must be met during recursion */

int recur(int n) {
    if (n<2) return n;
    return recur(n-1) + recur(n -2);
}
int main() {
    printf("%d", recur(5));
    return 0;
}
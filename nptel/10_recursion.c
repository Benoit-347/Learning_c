#include <stdio.h>

/* 2 conditions to be able to use recursion:
    i) problem expressible in a recursive form
    ii) a end condition must be met during recursion */

void recur(int n) {
    if (n <= 0) return;
    printf("n = %d at address %p\n", n, (void*)&n);
    printf("The prev n: %d\n", *(&n + 8)); // at address each unit of address id is 1 byte. Here &n + 1 moves address by 4 bytes (32 bit as int) For resaons, each n in recursion is 32 addresses (so 32 bytes) apart; Therefore (-8 for next n) +8 gives value of prev n. (* shows that to reference the address)
                                                                                                                                                                    // reasons: Overhead: Return address (8 bytes) + frame pointer (8 bytes) + alignment.
    recur(n - 1);
    printf("%dHello world\n", n*-1);
}
int main() {
    recur(3);
    printf("\n\n%d\n\n", recur_fibonnacci(40));
    return 0;
}



// theoratical fn-
int recur_fibonnacci(int n) {
    int b = 0;
    if (n<2) return n;
    return recur_fibonnacci(n-1) + recur_fibonnacci(n -2);
}   // this fn fails at more than 40th number due to exponential recur call behaviour
    // by no opti, max is 500000 frames (16 byte per frame) so ~ 2^15 or 15 is the max n in this function.

// Note: since a recur fn is local, after reaching end and returning, the data of it at stack is popped off, making space.
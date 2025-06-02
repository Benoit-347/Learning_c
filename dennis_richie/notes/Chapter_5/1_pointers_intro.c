// Consider variables hold values. These variables denote memory locations and when variables are accessed, these memory locations are accessed.
// The values at these memory locations are internally derefenced by the compiler hence ( printf("%d", a) )

// Pointers are address to that memory location. They hold address that points to that memory location/variable.

/* Consider: a = 5; a is X123A3BE
            mov x0, [X123A2BE]
            
            now using pointers,
            pointer = &a;
            mov x1, [pointer]       // here x1 is [x123A2BE]
            mov x0, [x1]*/

//pointers are of 8 bytes (due to 64 bit system; to all types- char, int, float)

#include <stdio.h>

int main(){
    int x = 1, y = 2;
    printf("Initial:\nx = %d\ny = %d\n", x, y);
    int *ptr;
    ptr = &x;
    y = *ptr;
    *ptr = 0;
    printf("\nFinal\nx = %d\ny = %d\n", x, y);

    return 0;
}

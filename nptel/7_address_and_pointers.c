#include <stdio.h>

int fn(int *x, int *y){
    int *temp = x;
    x = y;
    y = temp;
    printf("After swap: x points to %d, y points to %d\n", *x, *y);
}

int main(){
    int x = 0, y = 1;
    printf("Original value of x: %d value of y: %d\n", x, y);

    fn(&x, &y);

    printf("\nPart 2\n\n");

    int *p = &x, *q = &y;
    int *temp = p;
    p = q;
    q = temp;

    printf("After swap: p points to %d, q points to %d\n", *p, *q);   // Outputs: 10, 5

    return 0;
}
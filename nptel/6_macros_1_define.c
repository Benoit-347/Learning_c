#include <stdio.h>

# define sqrt1(x) x*x
# define sqrt2(x) (x)*(x)
# define sqrt3()    

int main(){

    int b;
    b = sqrt1(20+2);    // 20+2*20+2
    printf("1: %d\n", b);
    b = sqrt2(20+2);    // (20+2)*(20+2)
    printf("2: %d\n", b);
    }
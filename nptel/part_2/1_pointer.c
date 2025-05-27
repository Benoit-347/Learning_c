/*
static flat arrays have the 4 byte pointers not allowing *(*(arr +i)+j) method, instead i*j+arr method,
former was allowed for dynamic arrays, or use cast to [cols] pointer to use that method.
*/


#include <stdio.h>

// we know that variables are associated to their memory location during compilation (the vars are replaced to their addresses)
// pointers (the address) -> &a
// dereferece (address to value) -> *(&a)


//using pointers:
int main(){
    int a[10] = {1};
    int * b;     // int * <var_1>    means var_1 is enabled to point to int storeage values only

    b= &a;
    b = *b;
    printf("%d\n", b);  // & a == & a[0]

    // passing absolute address and trying to dereference it to obtain data value of a random bit in the computers stack

    b = 32000;
    printf("%d", *b);
}

#include <stdio.h>

int main(){
    struct struct1 {int a[4]; int b[5];};
    struct struct2 {struct struct1 name2; struct struct1 name3;};
    struct struct2 name = { { {1,2,3,4}, {11,12,13,14} }, { {101, 102, 103, 104}, {128,112,113,114} } };
    char *ptr = (char *) & name;
    // to print the second members first b element
    printf("The char pointed value: %d\n", *(ptr + 4 * (9 + 4) ));      // this pointer uses char address so even tho taking as %d, the max value is 127

    // using int pointer to get the full int result
    int *ptr1 = (int *) (ptr + 4 * (9 + 4) );
    printf("The int pointed value: %d\n", *ptr1);
    return 0;
}


# include <stdio.h>

int main(){
    int * p = (int *) calloc (100, 1);   // bytes, 1 each
    *p = 42;
    *(p + 1) = 100;
    printf("%d\n", *(p + 1));   // gives 100
    char * q = (char *) (p);
    *(q + 4*2 + 1) = 128;
    printf("%d\n", *(q + 4*2 +1));

    //what do you think is the output for:

    printf("%d\n", *(p + 2));

    // ans: 2^15 as this is the 2nd byte (i have a little endian system)         *(q + 4*2) is the 1st byte
    // big endian: arm sys
    return 0;
}
// pointers can be added by 1 to move the pointing location by 1.

// the final address of a pointer by addition of pointer is determined by its data type during declaration.
    // eg: char *ptr = &a; ptr++ -> puts the adr of ptr + 1 or points to next char element in a char array.    int *ptr -> ptr++ -> puts the adr of ptr + 4, or points to next int element in a int array

#include <stdio.h>

int main(){
    int a[10] = {11,12,13,14,15,16,17,18,19,20};

    int *ptr = &a[0];
    ptr = ptr + 1;
    printf("*(ptr + 1) = %d\n", *ptr);

    // the precedece of pointers are such when used with pointers: (pointer < increment)
    *ptr++;     //left: gets valaue at ptr++; (*ptr)++ adds 1 to *ptr
    printf("*ptr++ = %d\n", *ptr);  // value at a[2] not changed

    //but:
    printf("++*ptr = %d\n", ++*ptr); // along with arithementic expressions, follows left to right associvity.
    
    return 0;
}

// only arithemetic b/w 2 pointers is subtraction to return an int SHOULD NOT RETURN ANOTHER POINTER (eg: only for pointers of same array)
// which is disscussed in appl code.
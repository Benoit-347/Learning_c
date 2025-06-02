//faster: pointer subscripting > array array subscripting

// arrays are consequtive memory storage locations with the base name being synonomous to a pointer.
// the base name points to first element. The remaining elements are offset to the array name.  a[i] == *(a+i)

#include <stdio.h>

int main(){
    int a[10] = {11,12,13,14,15,16,17,18,19,20};
    int *b = &a[0];
    // &a[0] == a

    printf("The number: %d\n", b[2]);

    fn();

    return 0;
}

/* All Pointers can also do array subsripting;   ( As long as the memory location it subsripts is Valid)
    pointers to Array base names, like arrays can also do array subsripting*/

int fn(void){
    int arr[10] = {11,12,13,14,15,16,17,18,19,20};
    int *pt;
    pt = &arr[0];  
    pt = arr;    //equivalent to pt = (int *) arr;
    ++pt;   // now  puts the pointing from element a[0] to element a[1] -> 12
    printf("The number: %d\n", pt[1]);

    /*Note: Since arr is not a full on pointer (not a full on variable but, arr is an array name):
            Changes to array name not allowed: ++arr not allowed, and arr = ptr not allowed. */
    return 0;
    }
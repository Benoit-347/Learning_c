// using pointers to describe alloc

//A rudimentory storage allocator, alloc(n) returns pointer with n storage locations; afree(p) releases storage at p.

#include <stdio.h>

#define ALLOCSIZE 1000

char static alloc_buf[ALLOCSIZE];
char static * alloc_p = alloc_buf;  // current free position

char * alloc(int n);
void afree(char *p);
int main(){
    alloc(5);
    printf("The current pointer of alloc is: %p\nThe number of storage units: %d\n", alloc_p, alloc_p - alloc_buf); // pointer subtraction work case
    
}

char *alloc(int n){
    // check first if storage asked is available:
    if ( ALLOCSIZE + (alloc_buf - alloc_p) > n){ // The only case arithemetic b/w pointers work
        alloc_p += n;
        return alloc_p-n;   // to give initial pointer, before creating space.
    }
    else
        return 0;       // Used as a sign, Since 0 is not a valid address for data guaranteed by C.
}

void afree(char *p){    // re-freeing space -> simply by moving pointer back
    if (p >= alloc_buf && p < alloc_p)
        alloc_p = p;
}


// pointers can have the value 0 as well -> special case
// Often used as NULL to denote a 0 for a pointer.

// since poiters can return int by subtraction, it is reasonable to conclude that comparison can also be done b/w 2 pointers. Can use <, >, ==, etc.
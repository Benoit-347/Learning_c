#include <stdio.h>

// we know we can use a structure inside another structure, consider having a seq of such structs in address.

// an array of structs:
int main(){
    struct name {int a; float b;};
    struct name array_of_structs[50] = { {3, 4.5}, {10, 11.5}};

    printf("First member: %f\n", array_of_structs[1].b);

    temp();
    }

// note that when initialising a varialbe with the type <struct_name> , we use the word struct before it.
// This makes it so the name of the struct is not such that every time it occurs the compiler does not think of it as reffering to that defined struct (a keyword).


/* to create a keyword type struct,
    i) the keywrod property will be assigned to the var at the end (like creating vars of the struct type)
    ii) use the prefix typedef*/
int temp(){
    typedef struct {int a; int c;} complex, complex1;       // this makes both the same type (like int and int)
    complex name1 = {5, 1};
    complex1 name2 = {1, 0};
    printf("The temp fn:-    x: %d, i: %d", name1.a, name1.c);
    printf("The temp fn:-    x: %d, i: %d", name2.a, name1.c);
}
#include <stdio.h>



// accessing a struct:
int main(){
    struct name { int a; float b;};
    int a;

    struct name var1 = { 3, 4.0 };
    a = var1.a;     // strucute_name.member
    printf("%d\n", a);


    // nested member?

    struct name_nested { int a[5]; struct name member2;};
    struct name_nested name2 = { {1,2,3,4,5}, {3, 4.5}};
    printf("The nested member: %f\n", name2.member2.b);
}

// structs contain members inside them so they can be copied/assigned to another var_name as well (so unlike arrays: since they don't contain the elements, rather store them by realtive addressing)
// also, since 2 structures do not contain linear values, they cannot be compared or checked for equality
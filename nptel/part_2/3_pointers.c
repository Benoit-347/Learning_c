#include <stdio.h>

// usign pointers with structs
int main(){
    struct complex {int a; int b};
    struct complex name = {1, 2}, *p;
    p = &name;
    printf("%d\n", (p -> a));
    
}   // . is higher precedence than *,  "->" is highest precedence
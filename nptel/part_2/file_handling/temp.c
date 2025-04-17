
#include <stdio.h>
int main(){
struct p { int a; char b;};
struct p a[] = {1,2,3,4,5};
    printf("%d\n", a[2].b);
}
#include <stdio.h>

int loop_A(int i, int n, int j){
    j = j + 1;
    if(j == n)
    return i += j;
    i += j;
    return loop_A(i, n, j);

    // So it is a recursive fn
}




int main(){
    printf("Num: %d\n", loop_A(0, 10, 0));
}
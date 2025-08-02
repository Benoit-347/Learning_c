// A conditional operator is also an expression in C, so in any place where an expression can be used, you can also use a conditonal operator.
    // Allows for cmp usage, to then choose what to feed out from the expression.

//Eg:
# include <stdio.h>
int main(){
    int a = 2;
    int b = 5;

    printf("The output: %d\n", (a > b)? 1 : 0);
}
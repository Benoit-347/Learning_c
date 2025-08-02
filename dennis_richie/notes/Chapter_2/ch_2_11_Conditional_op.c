// A conditional operator is also an expression in C, so in any place where an expression can be used, you can also use a conditonal operator.
    // Allows for cmp usage, to then choose what to feed out from the expression.

//Eg:
# include <stdio.h>
int main(){
    int a = 2;
    int b = 5;

    printf("The output: %d\n", (a > b)? 1 : 0);


    // precedence for same precendece in single statement is decided by compiler like:
    printf("This is sys specific: %d %d\n", a++, a);
    // The precedence in C is: (), [], ->, .    general immidieate ops
                            // !, &, ++, --     Increment and address ops
                            // *, /, %          Mathematical ops
                            // + -
                            // << >>            Bit shift ops
                            // <, >, <=, >=     Cmp ops
                            // == !=
                            // &                Bit ops (only shift is above)
                            // ^
                            // |
                            // &&               Logical  ops
                            // ||
                            // ?:               Conditional operator
                            // =                Assignment operator
                            // ,                Comma or expression only and not return operator
}


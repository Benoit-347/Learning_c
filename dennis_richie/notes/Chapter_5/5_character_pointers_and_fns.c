#include <stdio.h>

int main(){

    // consider a string constant written as: "Hello, World!"
   
    // Internal representation: a constatnt array with \0 temminated.
    // Most commonly used in function arguments like:
    printf("Hello World!");     // here, when passing string constants, printf recieves a pointer to the beginning of the string constant.

    
    char *str = "Hello, World!"; // here the pointer to the beginning of the array is passed to the ptr str. (like str = &"H")
    
    printf("%s\n", str);  // Output: Hello, World!

    // "Hello World!" is a constant. Therefore, Attempting to modify the string literal is undefined behavior (usually results in segmentation fault). 
    // str[0] = 'h';  -> seg error



    return 0;
}
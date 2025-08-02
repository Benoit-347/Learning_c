//  Use case 1 (using defining macros with arguments):

#define printd(msg) printf(msg"\n")     //two string literals consequtively concatenate each other in C.

// Feature 2: Converting to string literals- prefix the argument parameter with # at location of replacement text

#define printd2(msg) printf(#msg"\n")   // IMP: intuitive convertion of a text entity to text entity enclosed into double quotes
                                                // so if msg was: "hello", #msg would return ""hello""" ?
// Use case 2:

#define printdexp(exp) printf(#exp" = %d\n", exp)

// Feature 3: create pure token, through directly merging two arguments by using double '#'   (merge i.e into txt not into a string) part 1 #exp would be a str and part 2 msg would be a number

#define paste(first, last) first ## last    //Use case 3: creating new tokens by merging two arguments (here seems to returns 1 token)
                                                // '##' removes any adjacent whitespaces (before and after '##') so paste("hello", "world") -> "hello""world"
#include <stdio.h>

int main(){
    printd("Hello World!");
    printd2(Hello World!);
    printdexp(4*3);    //Use case 2

    printf("paste(2, 1) = %d\n", paste(2, 1));
}
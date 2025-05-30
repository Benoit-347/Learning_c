// Syntax: 
    #define name "replacement text"

    // used to define a identifier that will be replaced by replacement text at all matches found in code
        // can stop this behavior using #undef to stop replacement for specified name, following this statement




// special feature: copy paste arguments by- name(Arg1, Arg2, Arg3...) Arg1*Arg2 ops

    // Feature of passing arguments using macros (with the aim of the macro body doing operations on the argument)
    # define max(A, B) ( (A) > (B) ? (A) : (B) )
        // substitutes the whole expression of macro body while also taking and passing the arguments to the expressions.
            // Normally define acts like putting text code directly, to achieve this more nuancedly we have containers that allow to copy the arguments and substitute the same arguments into expressions. (or this would be just letters A and B)
        
        //scope of #define: just like all variables, from point of declaration to end of file.

    #define a n*i   // can substitute the exact text as well evn tho the txt is not defined by itself (what max(A,B) would look like without arh copying feature)

#include <stdio.h>

int main(){int n = 10;
    int i = 5;
    printf(name"\n");
    printf("Max is %d\n", max(3, 5));
    printf("%d\n", n);
    return 0;    
}

/*Note: each time when we pass expresions to arguments, the expresions are copied as is to code,
        so for expressions like incr op that change value of var each the expression is used: max(i++, j++)
            The increment is done twice and the expression is evaluated twice (due to how basic substitution workd when the code is eval when substitued at main fn)*/
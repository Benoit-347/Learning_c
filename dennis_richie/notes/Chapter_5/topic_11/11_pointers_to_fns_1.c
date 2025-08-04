// Want to automatically make one fn, choose what fn to use? While also automatically taking parameters from the parent parameters?

/* Pass the fn name and mention each type of parameters used, and let the fn do the calling for you
    The indirect way of doing this was to use flags to denote different fns,
        And match flags and call the fns manually (instead of directly using the argument as fn name)
*/

#include <stdio.h>

int parent_fn(int (*comp)(int, int), int value1, int value2){   //Twostages, 1. shows the number of args for comp (int, int), 2. remaining optional parameters of parent
            // passes the fn comp to the first parameter, with the arguments to the comp fn being 2, both being casto to void *.
            
    if ( (*comp)(value1, value2) )  // using the rest of the parameter of parent to pass to comp fn.
        return 1;
    return 0;
}

int fn_1(int a, int b){ // normal fn_1
    if (a>b)
        return 1;
    printf("Fn 1 not true\n");
    return 0;
}

int fn_2(int a, int b){ // normal fn_2
    if  (!(a%10))
        return 1;
    printf("Fn 2 not true\n");
    return 0;
}

int main(){
    int a = 10, b = 5;
    if ( parent_fn((fn_2(a, b)? fn_1: fn_2), a, b)) // pass either fn_1 or fn_2 to the first para of parent.
        printf("Final: true\n");
    else
        printf("Final: Not true\n");
}


// Want to automatically make one fn, choose what fn to use? WHile also automatically taking parameters from the parent parameters?
    // passing a function to the parameter of another function:

// Program: two fns 1 and 2 return True or False, the main fn chks fn_2 is true, then returns ptr to fn_1, ptr to fn_2
#include <stdio.h>

int parent_fn(int (*comp)(int, int), int value1, int value2){   //Twostages, 1. shows the number of args for comp (int, int), 2. remaining optional parameters of parent
            // passes the fn comp to the first parameter, with the arguments to the comp fn being 2, both being casto to void *.
            
    if ( (*comp)(value1, value2) )  // using the rest of the parameter of parent to pass to comp fn.
        return 1;
    return 0;
}

int fn_1(int a, int b){ // normal fn_1
    if (a>b){
        printf("Reached inside fn 1: True\n");
        return 1;
        
    }
    printf("Reached inside Fn 1 not true\n");
    return 0;
}

int fn_2(int a, int b){ // normal fn_2
    if  (!(a%10)){
        
        printf("Reached inside fn 2: True\n");
        return 1;
    }
    printf("Reached inside Fn 2 not true\n");
    return 0;
}

int main(){
    int a = 10, b = 5;
    if ( parent_fn((fn_2(a, b)? fn_1: fn_2), a, b)) // pass either fn_1 or fn_2 to the first para of parent.
        printf("Reached inside Final: true\n");
    else
        printf("Reached inside Final: Not true\n");
}
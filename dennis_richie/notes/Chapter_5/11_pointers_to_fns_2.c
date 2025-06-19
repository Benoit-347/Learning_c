# include <stdio.h>

// program to do normal division by 2 for even and extra for odd:

float normal_divide(int a, int b){
    printf("Doing normal divide\n");
    return a/b;
}

float odd_divide(int a, int b){
    printf("Doing odd divide\n");
    return ( (float) a) / ( (float) b);
}

float do_divide( float (*fn)(int, int), int a, int b){  // gives ability to pass the fn names to this fn, which passes the parameters to it repectively.
    return (*fn)(a, b);
}


// doing all this proper automatically:

float do_auto_divide(float (*fn_1)(int, int), float (*fn_2)(int, int), int a, int b){   // req passing function names to the parent before hand (also since neccesary the fns para too)
    if (a%b)
        return (*fn_2)(a, b);
    else
        return (*fn_1)(a, b);

}


int main(){
    int a =  5, b = 10;
    float result;
    result = do_divide(  (a%b)? odd_divide: normal_divide, a, b);
    printf("Anwer is: %f\n", result);

    printf("The auto method: %f\n", do_auto_divide(normal_divide, odd_divide, a, b));
}

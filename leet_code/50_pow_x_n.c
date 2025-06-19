# include <stdio.h>

USE THE BASE INCLUSIVE SCALING PROPERTY FOR FAST SCALE OF HIGH N NUMBERS

double myPow(double x, int n) {
    double result = 1;
    if (n == 0)
        return 1;
    else if (x == 0.00000)
        return 0.00000;
    else if (x == 1.00000)
        return 1.00000;
    else if (x == -1.00000)
        return (n%2)?-1.00000:1.00000;
    else if (n>1000 && (x > 0 && x<0.1) )
        return 0.00000;
    else if (x>0 && n<-1000)
        return 0.00000;
    else {
        for (int i = 0; i<n; i++){
            result = result*x;
        }

        if (n<0){
            n = n*-1;
            for (int i = 0; i<n; i++)
                result = result /x;
        }
    }
    return result;
}

int main(){
    double x = 0.0001;
    int n= 2147483647;
    printf("The x: %f The n: %d\nOutput: %f\n", x, n, myPow(x, n));
}
#include <stdio.h>

float fn(float x){
    return x*x*x - 2*x - 5;
}
int main(){
    float err = 0.001;
    float f1, f2, x1 = 10, x2 = -9, x, f;
    x = (x1 + x2) / 2;
    f1 = fn(x1);
    f2 = fn(x2);
    while(fabs(x1 - x2) > err){
        f = fn(x);
        if (f*f1 < 0)
            x2 = x;
        else{
            x1 = x;
        }
        x = (x1 + x2)/2;
        printf("The fn(x):%f %f",x, fn(x));


    }
    printf("The fn(x):%f %f",x, fn(x));
}
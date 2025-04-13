#include <stdio.h>
#include <math.h>  // For fabs

float fun(float x) {
    return x*exp(2*x) - 3*x*x - 5;
}

void bisection(float *x, float a, float b, float allerr, int maxitr, int *itr) {
    *x = (a + b) / 2;  // Initial midpoint
    float fx = fun(*x);

    while (*itr < maxitr) {
        if (fun(a) * fx < 0) {
            b = *x;
        } else {
            a = *x;
        }
        *x = (a + b) / 2;
        fx = fun(*x);
        printf("Iteration no. %3d X = %7.5f\n", *itr, *x);
        (*itr)++;

        if (fabs(b - a) < allerr) {
            break;
        }
    }
}

int main() {
    int itr = 0, maxitr;
    float x, a, b, allerr;

    printf("Enter the values of a, b, allowed error and maximum iterations\n");
    scanf("%f %f %f %d", &a, &b, &allerr, &maxitr);

    // Check initial sign change
    if (fun(a) * fun(b) >= 0) {
        printf("No root in interval [%f, %f]\n", a, b);
        return 1;
    }

    bisection(&x, a, b, allerr, maxitr, &itr);

    if (fabs(b - a) < allerr) {
        printf("After %d iterations, root = %6.4f\n", itr, x);
    } else {
        printf("The solution does not converge or iterations not sufficient\n");
        return 1;
    }

    return 0;
}
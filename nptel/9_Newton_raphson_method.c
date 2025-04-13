#include <stdio.h>
#include <math.h>  // For log10 and fabs

// Function whose root we want to find
float f(float x) {
    return x * log10(x) - 1.2;
}

// Derivative of the function
float df(float x) {
    return log10(x) + 0.43429;  // Approximation of 1/ln(10)
}

int main() {
    int itr, maxitr;
    float x0, x1, allerr;

    printf("Enter x0, allowed error and maximum iterations\n");
    scanf("%f %f %d", &x0, &allerr, &maxitr);

    for (itr = 1; itr <= maxitr; itr++) {
        x1 = x0 - f(x0) / df(x0);  // Newton-Raphson iteration: x1 = x0 - f(x0)/f'(x0)

        printf("At iteration no. %3d, x = %9.6f\n", itr, x1);

        if (fabs(x1 - x0) < allerr) {
            printf("After %3d iterations, root = %8.6f\n", itr, x1);
            return 0;
        }

        x0 = x1;  // Update x0 for the next iteration
    }

    printf("The required solution does not converge or iterations are insufficient\n");
    return 1;
}
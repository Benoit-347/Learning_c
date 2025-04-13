#include <stdio.h>

#define pi 3.14159261111111110
#define fun(x) (x*x - x)

int main(void){
    unsigned int a = 4294967295;
    printf("%u\n", (a));
    float i = 37.0/fun(2);
    printf("%.2f\n", (i));
    int j, k;
    j = -3 % -2;
    printf("%d\n", j);
    while (1){
    printf("Hello\n");
    j = j + 1;
    if (j == 2)
    break;
    }
    i = 0;
    j = 0;
    j = i++ *50 + i++*i++;
    printf("%d\n", j);
    j = 10 * 20 > 100? 10:20;   // the ? is a if like operator than has lowest sig to its lhs, then based on it decides the value from its rhs
    printf("%d\n", j);          // called ternary operator

    switch (1){
    break;
}
    printf("ayo");
    printf("\n2. ");
    scanf("%c%c", &j, &k);
    printf("%d %d", j, k);


}

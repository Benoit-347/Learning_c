#include <stdio.h>

int main(){
    char value[5];
    char value1, value2;
    scanf("%s", &value);
    printf("the 5th byte: %d\n", value[4]);
    printf("%s", value);

    scanf("%d%d", &value1, &value2);
    printf("The d are: %d, %d\n", value1, value2);
}
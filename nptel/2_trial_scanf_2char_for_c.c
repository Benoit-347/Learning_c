#include <stdio.h>

int main(){
    char value[5];
    char value1, value2;
    // scanf %d format changes the way scanf takes input from terminal, for %d, it skips all whitespace and diffrent nos are seperated by whitespaces, when adding %c it takes in all chars and if a non digit is given to scanf with %d it gives %d garbage val and passed that non digit to %c
    scanf("%s", &value);
    printf("the 5th byte: %d\n", value[4]);
    printf("%s", value);

    scanf("%d%d", &value1, &value2);
    printf("The d are: %d, %d\n", value1, value2);
}
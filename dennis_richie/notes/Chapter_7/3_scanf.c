// mathces the fmt string to stdio, then takes stdio to the ptrs at arg
# include <stdio.h>

int main(){
    char day, month;
    int year;
    scanf("%d/%d/%d", &day, &month, &year);
    printf("%d-%d-%d\n", day, month, year);
    int c;
    c = getc(stdin);    // take the whitespacee
    c = getc(stdin);    // take the next char after the above \n skip
    printf("Get is: %c\n", c);
}
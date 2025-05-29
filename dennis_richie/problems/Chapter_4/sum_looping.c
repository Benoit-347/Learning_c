#include <stdio.h>

int start_loop(){
    int ch, sum = 0, num = 0;
    printf("Enter number: ");
    while ((ch = getchar()) != EOF) {
        if (ch == '\n'){
            sum += num;
            num = 0;
            printf("SUM: %d\n", sum);
        }
        else if (ch == ' '){
            sum += num;
            num = 0;
        }
        else if (ch >= '0' && ch <= '9')
            num = num*10 + ch - '0';
        else {
            printf("undefined character!\n");
            break;
        }
    }
}

int main(){
    start_loop();
}
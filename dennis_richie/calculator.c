#include <stdio.h>


int atoi(){
    char c, sign = 1;
    int num = 0;
    c = getchar();
    if (c == '-'){
        sign = -1;
        c = getchar();
        }
    else if (c == '+'){
        sign = 1;
        c = getchar();
        }

    while (isdigit(c)){
        num = num * 10;
        num = num +  (c - '0');
        c = getchar();
    }
    return sign*num;
}


int main(){
    int num = 0;
    char operator;
    char temp;
    int stack1[1000];


    while (temp = getchar()){
        if (isdigit(temp))
            num *= 10;
            num += temp - '0';
            continue;
        push(num);
        num = 0;
        
    }
}
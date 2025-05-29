# include <stdio.h>


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
    num = atoi();
    printf("The num: %d\n", num);
}
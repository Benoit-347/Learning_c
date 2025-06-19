# include <stdio.h>

    ERROR NEED TO HANDLE UPTO 10,000 DIGITS

    char str[20] = {0};

int str_to_int(char * arr, int * i){    // pass str arr and the index starting from the str int
    int num = 0;
    char ch;

    if (arr[*i] == '0')
        return 0;
    while ( (ch = arr[*i]) >= '0' && ch <= '9'){
        num = num*10 + (ch - '0');
        (*i)++; // this fn wven when exit, will keep i val at next element's index
    }
    printf("Num: %d\n", num);
    return num;
}

char * int_to_str(int val1, char * str){
    int temp = val1;
    char i = 0;
    if (val1 == 0){
        str[0] = '0';
        str[1] = 0;
        return str;
    }
    while (temp>0){
        temp = temp/10;
        i++;
    }

    str[i] = 0;
    while (val1>0){
        printf("Num: %d, val1: %d\n", i, val1);
        str[--i] = val1 % 10 + '0';
        val1 = val1/10;
    }
    return str;
}


char* addStrings(char* num1, char* num2) {
    int i = 0;
    int val1 = str_to_int(num1, &i);
    int j = 0;
    int val2 = str_to_int(num2, &j);
    val1 = val1 + val2;
    return int_to_str(val1, str);

}

int main(){
    char str1[] = "11";
    char str2[] = "123";
    printf("The result: %s\n", addStrings(str1, str2));
}
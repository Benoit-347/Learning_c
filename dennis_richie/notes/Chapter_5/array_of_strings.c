#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 1024
char *arr_buf[MAX_LINES];

// takes input into a given pointer until \n or EOF or max_line is reached
int get_line(char *str, int max_len){
    int n = 0;
    while ((*(str + n) = getchar()) != EOF && *(str + n) != '\n' && n < max_len - 1) {
        n++;
    }
    *(str + n) = '\0'; // null terminated string
    return n;
}   // returns number of char

// creates storage for each str arr and re uses it for input, copies it to new ptr through malloc to then be stored at an arr of s
int read_lines(){
    char str[MAX_LINE_LENGTH];
    char *str_new;
    int arr_lines = 0;
    int n = 0;
    while (n = get_line(str, MAX_LINE_LENGTH) > 0) {
        str_new = (char *) malloc(++n);
        strcpy(str_new, str);
        arr_buf[arr_lines++] = str_new;
    }
    return arr_lines;
}
int main(){

    int n_lines = read_lines();
    for (int i = 0; i<n_lines; i++){
        printf("Line %d: %s\n", i, arr_buf[i]);
    }
}
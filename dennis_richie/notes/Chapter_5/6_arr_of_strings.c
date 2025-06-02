// to get: get each line from input; put the line into an arr of size n.

# include <stdio.h>
# include <string.h>

#define MAX_LINE 1000
char arr_p[MAX_LINE];

int getline(char * str, int max_len){
    int i = 0;
    while ((*(str + i) = getchar()) != EOF && i<max_len){
        i++;
    }
    *(str + i++) = 0;
    return i;
}

int get_text(){
    char str[MAX_LINE];
    char *str_p;
    char *arr_ptr = arr_p;

    int n = get_line(*str, MAX_LINE);
    while (n > 0){
        str_p = malloc(n);
        strcpy(str_p, str);
        *arr_ptr++ = str_p;
        int n = get_line(*str, MAX_LINE);
    }
    *arr_ptr = 0;
}

int main(){
    get_text();
    for (int i = 0; arr_p[i] != 0; i++)
        printf("string %d: %s\n", i, arr_p[i]);
}
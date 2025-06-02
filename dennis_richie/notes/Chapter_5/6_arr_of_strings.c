# include <stdio.h>
# include <stdlib.h>
# include <string.h>

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 1024

char *arr_str[MAX_LINES];

// takes input into a given pointer until \n or EOF or max_line is reached
int get_line(char *str, int max_line){
    int n = 0;
    while((*(str + n) = getchar()) != '\n' && *(str + n) != EOF && n<max_line -1){
        n++;
    }
    *(str + n) = 0; // removes the last char that caused the end of loop and replaces to 0 (null terminated)
    return n;   
}

// to a given array of pointers;    take the values of string from a common str_ptr and copy to a unchnaging str_ptr whose ptr will be stored at arr of str.
int read_lines(char **ptr){

    char str[MAX_LINE_LENGTH];  // max size of each line
    char *str_storage;  // copy variable (arr poiner, using malloc)

    int str_len;    // used to obtain no. of chars from getline, to reduce malloc allocation.
    int lines = 0;  // counts every successful getline

    while(str_len = get_line(str, MAX_LINE_LENGTH) > 0){
        str_storage = (char *) malloc(str_len + 1); //converts allocation to char type
        strcpy(str_storage, str);   
        ptr[lines++] = str_storage; // post-fix makes sure the index lies 1 ahead (where ahead is free; also denotes no. of lines)
    }
    return lines;
}

int main(){
    int lines = read_lines(arr_str);    // The real function doing work

    for (int i = 0; i<lines; i++)   // displaying the text for each line in arr of str, using the info of nlines we provided from return.
        printf("Line %d: %s\n", i, arr_str[i]);
    
    return 0;
}
#include <stdio.h>

int search(char * line, char * pattern){
    int index = 0;
    for(int i = 0, j, k; line[i] != '\0'; i++){
        for(j = 0, k = i; pattern[j] != '\0'; j++){
            if (line[k] == pattern[j]){
                k++;
                continue;
            }
            break;
        }
        if (pattern[j] == '\0'){
            index = i;
            return  index;
        }
    }
}

int main(){
    char text1[] = "hello world this is text";
    printf("%d\n", search(text1, "world"));
    return 0;
}
#include <stdio.h>

int strlen(char string1[]){
    int i = 0;
    while(1){
        if (string1[i] == 0)
        return i;
        i++;
    }
}

int strcpy(char string1[], char string2[]){
    char condition;
    int i = 0;
    while(1){
    condition = string2[i];
    if (condition == '\0'){
        string1[i] = '\0';
        break;
        }
    string1[i] = condition;
    i++;
    }
}

int strcat(char string1[], char string2[]){

    int i = 0, j = 0;
    while(1){
        if (string1[i] == '\0')
        break;
        i++;
    }
    while(1){
        if (string2[j] == '\0')
        break;
        string1[i+j] = string2[j];
        j++;
    }
}

int strcmp(char string1[], char string2[]){
    int i = 0;
    while(1){
        if (string1[i] == '\0')
        break;
        i++;
    }

    int j = 0;
    while(1){
        if (string2[j] == '\0')
        break;
        j++;
    }

    if(i!=j)
    return 1;
    else{
        while(1){
            if (string1[i] != string2[i] | i == 0)
            return i;
            i--;
        }}
}

int main(){
    

    char string3[13] = "hello world\0", string4[26];
    int cmp, len;
    strcpy(string4, string3);
    printf("%s\n", string4);
    cmp = strcmp(string3, string4);
    printf("cmp: %d\n", cmp);
    strcat(string4, string3);
    printf("%s\n", string4);

    len = strlen(string4);
    printf("length: %d", len);
}

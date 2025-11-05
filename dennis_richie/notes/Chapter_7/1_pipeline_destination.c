// this file takes the output of another program as input for this program.

# include <stdio.h>

int main(){
    char initial_string[1000];
    int arr[100] = {0};
    gets(initial_string);
    printf("Found string from pipeline: %s\n", initial_string);
    for (int i = 0; i<10; i++)
        scanf("%d", arr + i);

    for (int i = 0; arr[i]; i++)
        printf("Obtained number %d from pipeline!\n", arr[i]);
}
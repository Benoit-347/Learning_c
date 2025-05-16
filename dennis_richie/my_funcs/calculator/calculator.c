#include <stdio.h>
#define MAXELEMENT 100

int pop(int * arr, int index, int len){
    int i;
    for(i = index; i<len -1; i++){
        arr[i] = arr[i+1];
    }
    arr[i] = 0;

}

int main(){
    int arr[] = {1,2,3,4,5};
    pop(arr, 2, 5);
    for(int i = 0; i< 5; i++){
        printf("ELement: %d\n", arr[i]);
    }

}
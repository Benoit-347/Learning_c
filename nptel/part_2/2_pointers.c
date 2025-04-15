#include <stdio.h>

// pointer expressions:
int main(){
    int *p, *q;
    p = 1;
    p += 0;     // increases address with the step of its unit size (here 4 bytes)
    printf("%p\n", p);
    q = 1;p = (int *)((int)p + (int)q);    // increases address with the step of its unit size (here 4 bytes)
    printf("%p\n", p);
    p = p-q;    // since the prev uses int to *int conversions, the stack will have corrption, so use the pointers to represent actual memory address in the stack to avoid unexplained behavior
    printf("%p\n"), (void *) p;

    int arr[10];
    for (int i = 0; i<10; i++){
        arr[i] = i + 1;
    }
    printf("%d\n", arr_avg(&arr, 10));  //  arr == &arr[0]

    printf("%d\n", arr[0]);     // when printing arr, it gives the address of arr, when printing arr[0], it prints the value stored at arr[0]
    
}

int main2(){

}


int arr_avg(int *arr, int num_ele){
    int sum = 0;
    for (int i = 0; i< num_ele; i++){
        sum += *(arr + i);
    }
    return sum;
    
}
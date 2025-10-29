# include <stdio.h>

// there are two ways to use high and low variables in binary search- using high as the last element pos of arr ( [low, high] ) or using high as last element + 1 pos,
    // while using inclusive low, high, we use low: mid +1, high: mid -1 ( -1 of mid for high is optional as x/2 tends to go to floor), then put condition of end search as if (low <= high) for the edge case of first element search.
        // while using [low, high), we use low: mid -1, high: mid and condition if (low < high) (the low < high condition is mandatory to avoid overgo at last element + 1 pos; following this due to low <=high being restricted we cannot put high: mid -1 as this would skip 1 elements at lower half (as now low and high cannot overlap to one element).

int * binary_search(int * arr, int max_len, int key){
    int * low = arr;
    int * high = arr + max_len;
    int * mid = 0;

    while (low< high){
        mid = low + (high - low)/2;  // pointer subtraction to find int difference first, then add to ptr low
        if (*mid == key)
            return mid;
        else if (key < *mid)
            high = mid;
        else
            low = mid + 1;
    }
    
    return 0;   // falls back here, if not returned at match if block
}

int main(){

    // trials

    // arr 1
    int arr[] = {1, 5, 8, 90, 100, 101, 190, 200, 250, 300, 500, 700};
    int count = sizeof(arr)/4;
    for (int i= 0; i<count; i++){
        int * found_ptr = binary_search(arr, count, arr[i]);
        if (found_ptr)
            printf("position of key\t %d \t is \t %d\n", arr[i], found_ptr - arr);
        else 
            printf("Not found key\t %d \n", arr[i]);
    }
    printf("\n");

    //arr 2
    int arr_2[] = {1, 5, 8, 90, 100, 101, 190, 200, 250, 300, 500, 700, 800};
    int count_2 = sizeof(arr_2)/4;
    for (int i= 0; i<count_2; i++){
        int * found_ptr = binary_search(arr_2, count_2, arr_2[i]);
        if (found_ptr)
            printf("position of key\t %d \t is \t %d\n", arr_2[i], found_ptr - arr_2);
        else 
            printf("Not found key\t %d \n", arr_2[i]);
    }
    printf("\n");
    
    //arr 3
    int arr_3[] = {1, 5, 8};
    int count_3 = sizeof(arr_3)/4;
    for (int i= 0; i<count_3; i++){
        int * found_ptr = binary_search(arr_3, count_3, arr_3[i]);
        if (found_ptr)
            printf("position of key\t %d \t is \t %d\n", arr_3[i], found_ptr - arr_3);
        else 
            printf("Not found key\t %d \n", arr_3[i]);
    }
    printf("\n");
    
    //arr_4 4
    int arr_4[] = {1, 5};
    int count_4 = sizeof(arr_4)/4;
    for (int i= 0; i<count_4; i++){
        int * found_ptr = binary_search(arr_4, count_4, arr_4[i]);
        if (found_ptr)
            printf("position of key\t %d \t is \t %d\n", arr_4[i], found_ptr - arr_4);
        else 
            printf("Not found key\t %d \n", arr_4[i]);
    }
    printf("\n");
    
    //arr_5 5
    int arr_5[] = {1};
    int count_5 = sizeof(arr_5)/4;
    for (int i= 0; i<count_5; i++){
        int * found_ptr = binary_search(arr_5, count_5, arr_5[i]);
        if (found_ptr)
            printf("position of key\t %d \t is \t %d\n", arr_5[i], found_ptr - arr_5);
        else 
            printf("Not found key\t %d \n", arr_5[i]);
    }

    return 0;
}
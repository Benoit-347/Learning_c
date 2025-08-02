# include <stdio.h>

int main(){
    int arr[] = {20, 5, 2, 11, 1};
    char n = 5;
    int temp;

    for (int i = 0; i<n; i++)   // only used to do seq checking of arr[j] and arr[j+1] -> also contributing to length of seq checking (with the j-i cond)
        for (int j = 0; j<n-1-i; j++)   // j<n to not count the empty element due to lenght index mismatch.     - 1 to remove cmp with air since j+1 is also accessed,      -i to ignore the last sorted elements by bubble sort nature
            if (arr[j] > arr[j+1]){
                temp = arr[j];      // simple 3rd var swap
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }

    // printing all elements
    for (int i = 0; i<n; i++)
        printf("Element %d is: %d\n", i, arr[i]);

    return 0;
}
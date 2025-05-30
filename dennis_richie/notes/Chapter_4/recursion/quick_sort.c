// Using recursion to sort an array (similar to qsort from the libriary) 62quick_sort develeoped by C.A.R Hoare 19

#include <stdio.h>

// my version

/* idea: In a unsorted array, divide the array at a specific element giving 2 subsets.
        The recur done for subsets until a single element is reached. */


# include <stdio.h>

int count_iterations= 0;

int swap(int v[], int left, int right){
    int temp;
    temp = v[left];
    v[left] = v[right];
    v[right] = temp;
}

void qsort ( int v[], int left, int right){
    int i , last;
    count_iterations++;
    if (left >= right)
        return;
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (v[i] < v[left])
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last -1);
    qsort(v, last +1, right);
}
int main(){
    int arr[] = {3,1,2,5,4};
    int left = 0, right = 4;
    qsort(arr, left, right);
    for(int i = 0; i<=right; i++)
        printf("arr[%d] = %d, ", i, arr[i]);
    printf("\nCount is: %d", count_iterations);
    return 0;
}

// this sorting is faster than bubble sort, selection sort and insertion sort on average case. Best case: insertion 
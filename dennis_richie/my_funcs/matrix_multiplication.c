// Program from college to multiply 2 3*3 matrixes and store them at a 3rd matrix.

#include <stdio.h>

int print_3_3(int * a){
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            printf("The value of c[%d][%d] = %d\n", i, j, *(a + (i*3 + j)));
                                                            // or *(*(a + i) + j)
                                                            // or simply take and pass argument as int a[]

    return 0;
}

int main(){
    int A[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
    int B[3][3] = {{11,12,13}, {14,15,16}, {17,18,19}};
    int c[3][3] = {0};

    // now for a m*n and p*q matrix, we intuitively have 2 sequence of option to choose:
        // 1st matrix row wise (m), nested: 2nd matrix column wise(q): where the element of n with p is multiplied sequencially
        // or 1st q then m:

    for (int m = 0; m<3;m++)
        for (int q = 0; q<3; q++)
            for (int i = 0; i<3; i++)
                c[m][q] += A[m][i] * B[i][q];    // fourth loop of p not req as p = n, as this is also a mandatory thing so can get around doing it
    
    //printing it:
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            printf("The value of c[%d][%d] = %d\n", i, j, c[i][j]);
    

    // the 2nd method we talked about:
    for (int q = 0; q<3; q++)       // the m and q are interchanged, this is the only change rest of the code here is same as prev
        for (int m = 0; m<3; m++){
            c[m][q] = 0;
            for (int i = 0; i<3; i++)
                c[m][q] += A[m][i] * B[i][q];}

    print_3_3((int *) c);
    
    return 0;

}
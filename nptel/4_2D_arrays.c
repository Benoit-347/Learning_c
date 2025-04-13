#include <stdio.h>


int main(){
    // array to provide numbers
    int a[10];
    for(int i =0; i<10; i++)
    a[i] = i;

    // create a matrix i*3 + j
    int matrix_1[3][3];
    for(int i =0; i<3; i++){
        for(int j =0; j<3; j++){
            matrix_1[i][j] = a[i*3+j];
        }
    }

    // create a matrix i*3 + j with 10 offset
    int matrix_2[3][3];
    for(int i =0; i<3; i++){
        for(int j =0; j<3; j++){
            matrix_2[i][j] = a[i*3+j] + 10;
        }
    }

    // addition of the two matrices
    int matrix_3[3][3];
    int m = 2, n = 2;

    for(int m = 2; m>=0; m--){
        for(int n = 2; n>=0;n--){
            matrix_3[m][n] = matrix_1[m][n] + matrix_2[m][n];
        }
    }

    for(int i = 0; i<3; i++){
        for(int j =0; j<3; j++){
            printf("row: %d\ncolumn: %d\nvalue: %d\n", i, j, matrix_3[i][j]);
        }
    }

}
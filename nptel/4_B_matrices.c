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

        int matrix_3[3][3];
        for(int i = 0; i<3; i++){
            for(int j = 0; j < 3; j++){
                matrix_3[i][j] = matrix_2[i][j] + matrix_1[i][j];
            }
        }

        for(int i = 0; i<3; i++){
            for(int j = 0; j<3; j++){
                printf("Row: %d\n Column: %d\n Value: %d\n", i, j, matrix_3[i][j]);
            }
        }
}
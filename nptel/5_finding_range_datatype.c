# include <stdio.h>

int main(){
    long double The_int = 1.0;
    long double temp;
    long double temp2;
    while(1){
        temp = The_int;
        The_int = The_int * 2;
        if (The_int /2 > temp){
            while(1){

                temp2 = temp;
                temp += temp/2;
                if (temp /2 > temp2){
                printf("The highest value: %Lf\nThe next value: %Lf\n", temp2, temp);
                break;
                }

            }
        break;


        }

    }
}
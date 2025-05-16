#include <stdio.h>
#define MAXELEMENT 100

int * create_calc_input(){
    static int arr[MAXELEMENT], num = 0, input, i;
    for(i = 0; (i<MAXELEMENT) && (input = getchar()) != '\n';){
        if (input >= '0' && input <= '9'){
            num = num*10 + input - '0';
        }

        else if (input = ' '){
            arr[i] = num;
            num = 0;
            i++;
        }
    }
    arr[i] = num;
    num = 0;
    i++;
    return arr;
}

int main(){
    int * arr = create_calc_input();
    for (int i = 0; i<10;i++){
        printf("ELement %d: %d\n", i, arr[i]);
    }
    return 0;

}
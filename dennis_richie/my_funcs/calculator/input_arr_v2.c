#include <stdio.h>
#define MAXELEMENT 100

int * create_calc_input(){
    static int arr[MAXELEMENT];
    int special_flag = 0, num = 0, input, i;
    for(i = 0, special_flag = 0; (i<MAXELEMENT) && (input = getchar()) != '\n';){
        if (input >= '0' && input <= '9'){
            num = num*10 + input - '0';
        }


        else if (input == ' ' && special_flag == 0){
            arr[i] = num;
            num = 0;
            i++;
        }

        else if (input == ' '  && special_flag ==1){
            special_flag = 0;
            continue;
        }
        
        switch (input)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            special_flag = 1;
            arr[i] = input;
            i++;
            break;
        
        default:
            break;
        }


    }
    if (special_flag == 0){
        arr[i] = num;
        num = 0;
    }

    return arr;
}

int main(){
    int * arr = create_calc_input();
    for (int i = 0; i<10;i++){
        printf("ELement %d: %d\n", i, arr[i]);
    }
    return 0;

}
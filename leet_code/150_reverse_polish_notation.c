/*
Input: tokens = ["2","1","+","3","*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9

Example 3:

Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
Output: 22
Explanation: ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22
*/

#include <stdio.h>

int get_ele_no_i_change(char **tokens, int i){
    return *tokens[i];  // obtain the char value at the i'th index of array tokens which is a pointer to a arr of chars (therefore here giving the first char of string)
}

int str_to_int(char *s){
    int i = 0, num = 0;
    char flag_sign = 1, ch;
    if (s[i] == '-'){
        flag_sign = -1;
        i++;
    }
    while ( (ch = s[i++]) != 0 )
        num = num*10 + ch - '0';

    return flag_sign*num;
}


int calc_duo_opers(int operand_1, int operand_2, char oper_1){  // reused simple fn to calc 2 operands
    switch (oper_1){
        case '+' :
            return operand_1 + operand_2;
            break;
        case '-' :
            return operand_1 - operand_2;
            break;
        case '*' :
            return operand_1 * operand_2;
            break;
        case '/' :
            return operand_1 / operand_2;
            break;
        default:
            printf("oper_1 Unmatched at duo: %d\n", oper_1);
            return 0;
    }
}

int evalRPN(char** tokens, int tokensSize) {
    int operand_1, operand_2, oper_1, i = 0, j = 0, ele;
    char arr[tokensSize/2 + 1];

    if (tokensSize ==1)
        return str_to_int(tokens[i]);

    while (i< tokensSize){

        // to diff b/w a num and a special char, we simply check the first char of string (for each index),
        ele = get_ele_no_i_change(tokens, i);
        
        // depending on if ele is a digit or special char, we put the num into another array or, perform operation on array hence removing 1 operand at the same array.
        if (ele >= '0' && ele <= '9' || (ele == '-' && *((tokens[i]) + 1)) ){    // (intuitive check ignore '-' chk, if only <|| *((tokens[i]) + 1)> since no char at second ele for special, True if the secong char at the string at arr element is anything but 0. 
            arr[j++] = str_to_int(tokens[i]);
            //printf("pushed val: %d\n", str_to_int(tokens[i]));
        }
        else{
            printf("i:%d -> Operand_1: %d operand_2: %d oper_1: %c; eval = %d\n", i, arr[j-2], arr[j-1], ele, calc_duo_opers(arr[j-2], arr[j-1], ele));

            arr[j-2] = calc_duo_opers(arr[j-2], arr[j-1], ele);              // at LHS need to put ans back at 2nd from last, -> -1 for 1st, -2 for 2nd
            j--;
        }
        i++;
    }
    return arr[0];
}


int main(){
    char *arr[13] = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"};
    printf("\nOutput: %d\n\n", evalRPN(arr, 13));
}
/*
Idea: (aim is memory efficiency): while ietering seq over main arr of strs, perform evals then store the result within the same arr
    So, need to conv to a str with static/global memory to be able to create str and replace ele at tokens (done at below code, rn till here), but problem now is in continuously creating arrys of chars; and also deleting prev allcated strs; need manual user def cod of alloc;
                                                                                                                                                                                                                                                // so also may need to start string new strs/ char arrys at local scope (eval_fn)
*/

#include <stdio.h>

char get_ele_no_i_change(char **tokens, int i){
    return *tokens[i];  // obtain the char value at the i'th index of array tokens which is a pointer to a arr of chars (therefore here giving the first char of string)
}

char str_to_int(char *s){
    int i = 0;
    char flag_sign = 1, ch, num = 0;;
    if (s[i] == '-'){
        flag_sign = -1;
        i++;
    }
    while ( (ch = s[i++]) != 0 )
        num = num*10 + ch - '0';

    return flag_sign*num;
}

char * conv_int_to_str(char val){
    static char arr[3] = {0};
    char i = 2;

    while (val){
        arr[i--] = val%10 + '0';
        val = val/10;
    }
    return arr;
}

char calc_duo_opers(char operand_1, char operand_2, char oper_1){  // reused simple fn to calc 2 operands
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

char evalRPN(char** tokens, int tokensSize) {
    char operand_1, operand_2, oper_1, i = 0, j = 0, ele;

    if (tokensSize ==1)
        return str_to_int(tokens[i]);

    while (i< tokensSize){

        // to diff b/w a num and a special char, we simply check the first char of string (for each index),
        ele = get_ele_no_i_change(tokens, i);
        
        // depending on if ele is a digit or special char, we put the num into another array or, perform operation on array hence removing 1 operand at the same array.
        if (ele >= '0' && ele <= '9' || (ele == '-' && *((tokens[i]) + 1)) ){    // (intuitive check ignore '-' chk, if only <|| *((tokens[i]) + 1)> since no char at second ele for special, True if the secong char at the string at arr element is anything but 0. 
            // CHANGE THIS LINE TO ACCOMODATE CREATED STRS, THEN STORE TO CHAR ** TOKENS
            tokens[j++] = str_to_int(tokens[i]);
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
    printf("int 120 to string: %s\n", conv_int_to_str(120));
}
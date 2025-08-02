/*
Example 1:

Input: num = "123", target = 6
Output: ["1*2*3","1+2+3"]
Explanation: Both "1*2*3" and "1+2+3" evaluate to 6.
Example 2:

Input: num = "232", target = 8
Output: ["2*3+2","2+3*2"]
Explanation: Both "2*3+2" and "2+3*2" evaluate to 8.
*/


int str_to_int(char * arr, int * i){    // pass str arr and the index starting from the str int
    int num = 0;
    char ch;
    while ( (ch = arr[*i]) >= '0' && ch <= '9'){
        num = num*10 + (ch - '0');
        (*i)++; // this fn wven when exit, will keep i val at next element's index
    }
    return num;
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

int i = 0;
char opers[] = "+-*/";
int recur(char* num, int target, int i, int j){
    for (; num[i]; i++)
        for (int j = 0; opers[j]; j++)
            return calc_duo_opers(num[i]-'0', recur(num, target, i+1), opers[j]);

    return 0;



char** addOperators(char* num, int target, int* returnSize) {

    }
}
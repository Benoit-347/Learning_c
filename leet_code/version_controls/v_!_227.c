/*Given a string s which represents an expression, evaluate this expression and return its value. 

The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

Example 1:

Input: s = "3+2*2"
Output: 7
Example 2:

Input: s = " 3/2 "
Output: 1
Example 3:

Input: s = " 3+5 / 2 "
Output: 5
 */



# include <stdio.h>

int str_to_int(char * arr, int * i){    // pass str arr and the index starting from the str int
    int num = 0;
    char ch;
    while ( (ch = arr[*i]) >= '0' && ch <= '9'){
        num = num*10 + (ch - '0');
        (*i)++; // this fn wven when exit, will keep i val at next element's index
    }
    return num;
}


// While iterating seq left to right of arr, make divisions of first and second operand, with first operator. Then also find second operator -> which will then be enclosed in a loop when it is * or / unitl the second operator is not * or /. then return the output to total.
// So have total, num, op1, op2. where the nested loop will do operatrions to num variable.

    // put the i at the latest ele after geting opers.
int get_opers(char * s, int *j, int * operand_1, int * operand_2, int *operand_3, char * oper_1, char * oper_2){
    int i = *j;
    //skip whitesspace:
    while (s[i++] == ' ')   // cond is evaluated at the last causing the last i to incr,
        ;
    i--;

    *operand_1 = str_to_int(s, &i);  // i now at new ele

    while (s[i++] == ' ')   // cond is evaluated at the last causing the last i to incr,
        ;
    i--;

    *oper_1 = s[i++];

    while (s[i++] == ' ')   // cond is evaluated at the last causing the last i to incr,
        ;
    i--;

    *operand_2 = str_to_int(s, &i);  // i now at new ele

    while (s[i++] == ' ')   // cond is evaluated at the last causing the last i to incr,
        ;
    i--;

    *j = i; // updating original passed j value.

    if (s[i] == 0)
    return 0;   // indicates end of calc and no more 2nd oper

    *oper_2 = s[(*j)++];
    return 1;   // indicates extra second oper.
}

int calculate(char* s) {
    int operand_1, operand_2, operand_3;
    char oper_1, oper_2;
    int i = 0;
    char ch;
    int total;

    get_opers(s, &i, &operand_1, &operand_2, &operand_3, &oper_1, &oper_2);

    printf("Operand_1: %d\nOper_1: %c\n", operand_1, oper_1);

}

int main(){
    char arr[] = " 3+5 / 2 - 2 + 3 * 4";
    calculate(arr);
    //printf("Output: %d\n", calculate((char *) arr));
    return 0;
}
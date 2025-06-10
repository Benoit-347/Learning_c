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

void clear_whitespace(char * s, int * i){   // shift i over whitespaces (skip all ' ')
    while (s[(*i)++] == ' ')   // cond is evaluated at the last causing the last i to incr,
        ;
    (*i)--;
}

int str_to_int(char * arr, int * i){    // pass str arr and the index starting from the str int
    int num = 0;
    char ch;
    while ( (ch = arr[*i]) >= '0' && ch <= '9'){
        num = num*10 + (ch - '0');
        (*i)++; // this fn wven when exit, will keep i val at next element's index
    }
    return num;
}
/*
int chk_opers(char * s, int i){ // i is copied

    int temp_operand_1, temp_operand_2;
    char temp_oper_1, temp_oper_2;
    
    //skip whitesspace:
    clear_whitespace(s, &i);

    temp_operand_1 = str_to_int(s, &i);  // i now at new ele

    clear_whitespace(s, &i);

    if (s[i] == 0)
        return 1;   // indicates number of operands until end of arr (i is now at)
    
    temp_oper_1 = s[i++];

    clear_whitespace(s, &i);

    temp_operand_2 = str_to_int(s, &i);  // i now at new ele

    clear_whitespace(s, &i);


    if (s[i] == 0)
    return 2;   // indicates 2 number of operands

    temp_oper_2 = s[i++];
    return 3;   // indicates 3rd operands (or more), i at the 3rd operand.
}

*/

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
    }
}

int calculate(char* s) {
    int operand_1, operand_2, operand_3;
    char oper_1, oper_2 = '+';
    int i = 0;
    char ch;
    int total = 0;

    clear_whitespace(s, &i);
    operand_1 = str_to_int(s, &i);
    clear_whitespace(s, &i);

    // tackling single input
    if (s[i] == 0)
        return operand_1;

    oper_1 = s[i++];

    // tackling operand_1 seq of multi or divi
    while (oper_1 == '*' || oper_1 == '/'){
        clear_whitespace(s, &i);
        operand_2 = str_to_int(s, &i);

        operand_1 = calc_duo_opers(operand_1, operand_2, oper_1);

        clear_whitespace(s, &i);
        // tackling only operand_1 of seq * and / input
        if (s[i] == 0)
            return operand_1;

        oper_1 = s[i++];
    }

    // now operand_1 is complete, moving on to a continuos taking of operand_2:
        // Preparing for operand_2 loop:
    clear_whitespace(s, &i);
    operand_2 = str_to_int(s, &i);
    clear_whitespace(s, &i);

    if (s[i] == 0)
        return calc_duo_opers(operand_1, operand_2, oper_1);

    

    // main loop since operand_1. (after multi/divi eval seq of operand_2, operand_1 will now starting totaling the additions and subtractions)
    while (s[i] != 0){

        oper_2 = s[i++];
        // operand_2 loop
        while (oper_2 == '*' || '/'){
            clear_whitespace(s, &i);
            operand_3 = str_to_int(s, &i);
            operand_2 = calc_duo_opers(operand_2, operand_3, oper_2);

            clear_whitespace(s, &i);

            if (s[i] == 0)
                return calc_duo_opers(operand_1, calc_duo_opers(operand_2, operand_3, oper_2), oper_1);

            oper_2 = s[i++];
        }

        // oper_2 now contains '+' or '-'
        operand_1 = calc_duo_opers(operand_1, operand_2, oper_1);
        oper_1 = oper_2;
        clear_whitespace(s, &i);
        operand_2 = str_to_int(s, &i);
        clear_whitespace(s, &i);
        
    }

    return operand_1;
}

int main(){
    char arr[] = " 3*4/12 - 20*3"; //" 3*4/12 -5/2*4 - 34+ 24/12 ";
    //calculate(arr);
    printf("Output: %d\n", calculate((char *) arr));
    return 0;
}
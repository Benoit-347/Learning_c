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


// While iterating seq left to right of arr, make divisions of first and second operand, with first operator. Then also find second operator -> which will then be enclosed in a loop when it is * or / unitl the second operator is not * or /. then return the output to total.
// So have total, num, op1, op2. where the nested loop will do operatrions to num variable.

    // put the i at the latest ele after geting opers.
int get_opers(char * s, int *j, int * operand_1, int * operand_2, char * oper_1, char * oper_2){
    int i = *j;
    //skip whitesspace:
    while (s[i++] == ' ')   // cond is evaluated at the last causing the last i to incr,
        ;
    i--;

    *operand_1 = str_to_int(s, &i);  // i now at new ele

    while (s[i++] == ' ')   // cond is evaluated at the last causing the last i to incr,
        ;
    i--;

    if (s[i] == 0)
        return 0;   // indicates end of calc and no more 2nd oper
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

    while ( get_opers(s, &i, &operand_1, &operand_2, &oper_1, &oper_2) ){   /// i val is now latest ele
        while (oper_1 == '*' || oper_1 == '/'){
            operand_1 = calc_duo_opers(operand_1, operand_2, oper_1);
            clear_whitespace(s, &i);
            operand_2 = str_to_int(s, &i);
            clear_whitespace(s, &i);
            if (s[i] == 0)
                break;
            oper_1 = s[i++];
        }
            // operator_1 now containes the seq of * and /, next is + or -

           // after ops the i is either at 0 or new operand (getops and oper_1 i++ at inner while)
            while (oper_2 == '*' || oper_2 == '/'){
                
                clear_whitespace(s, &i);

                operand_3 = str_to_int(s, &i);

                printf("1. BEFORE: Operand_1: %d operand_2: %d operand_3: %d\n", operand_1, operand_2, operand_3);
                
                operand_2 = calc_duo_opers(operand_2, operand_3, oper_2);
                
                clear_whitespace(s, &i);

                if (s[i] == 0)
                    break;
                else
                    oper_2 = s[i++];
            }

            printf("2. Operand_1: %d operand_2: %d\n", operand_1, operand_2);

            // the return of operand 2 and operand 3 are wrt oper_1 computed with operand_1
            total += calc_duo_opers(operand_1, operand_2, oper_1);
            printf("3. Total is: %d\n", total);
        }
    // after the while loop of getops (returns 0 if no oper_2)

    // the cond is evaluated meaning the i is now also at 0, end of str, (along with operand and oper 1 changed)

    printf("operand_1 : %d, 2: %d, oper: %c\n", operand_1, operand_2, oper_2);
    total = calc_duo_opers(total, operand_1, oper_1);

    //total = calc_duo_opers(total, calc_duo_opers(operand_1, operand_2, oper_1), oper_2);


    return total;

}

int main(){
    char arr[] = " 3*4/12 -5/2*4 - 34+ 24/12 ";
    //calculate(arr);
    printf("Output: %d\n", calculate((char *) arr));
    return 0;
}
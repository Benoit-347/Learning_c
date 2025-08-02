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

/*  Intro: working Works of principle of 
        i) doing eval on higher precedence to lower
        ii) doing eval left to right

    The operations this problem is concerned with is only *,/ or +, -; Left to Right.
        Only 2 levels of precedence causing If first operands operator (here oper_1) is *,/ do the whole eval until not *,/
            2 precedence only, we can simply evaluate the *,/ first and if its not the *,/ it would be +,-.
            Then this eval is done and stored to operand_1 to act as operand for next eval (with +,- for operand_2)
                Before eval operand_2, in case operand_2's oper; oper_2 contains the higher precedence *,/ we have to eval operand_2, with operand_3 along oper_2.
                    After seq eval of operand_2 with next until not *,/ (note*) the eval of the seq of operand_2 section is stored, at the variable operand_2   (note: here therefore here only being same precednce of +,-) 
                        This structure of storage of operand_1, and operand_2 allows doing multiple such evals, seq storing result at operand_1 and operand_2 which then after *,/ stage is evaluated again. (see next line for more)
                            The operand_1 after eval, oper_1 now contains +,- is remained with until until the duration of operand_2. 
                            Operand_2 is evaluated almost similar to operand_1's seq eval and then oper_2 now containes +.-
                            This operand_1 and operand_2 is evaluated with the now lower precedence +,-; and stored at operand_1 (for furthe expressions as just done from above i.e from second operand (since seq eval operand_2 and lower prece +,- with operand_1 storing to operand_1))
                            Further next evaluation:
                                The next operator was stored at oper_2, will be brought to oper_1; operand_2 needs to now be evaled this req to again check oper after operand_2, which Now being end of loop goes to start (cond if \0 evaled) and obatains the operator after operand_2, i.e oper_2 = s[i++];
                                    And so the loop caused this continues evals
                                Endpoints: at every eval of the operand afer oper, it is checked if s[i] ==0, if true returns the answer next line, after evaluating the prev (+,-) stored up values.

                                Source: my prev bugged getops code, to bedtime though of seq eval from the simple + - calc, to metro paper ideation, to realizing in code.
*/
int calculate(char* s) {
    int operand_1, operand_2, operand_3;
    char oper_1, oper_2 = '+';
    int i = 0;
    char ch;
    int total = 0;

    clear_whitespace(s, &i);
    // get first num
    operand_1 = str_to_int(s, &i);
    clear_whitespace(s, &i);

    // tackling single input
    if (s[i] == 0)
        return operand_1;


    // get first oper
    oper_1 = s[i++];

    // loop tackling operand_1 seq of multi or divi
    while (oper_1 == '*' || oper_1 == '/'){
        clear_whitespace(s, &i);
        operand_2 = str_to_int(s, &i);

        operand_1 = calc_duo_opers(operand_1, operand_2, oper_1);

        clear_whitespace(s, &i);
        // tackling only operand_1 of seq * and / input
        if (s[i] == 0)
            //Endpoint 1:
            return operand_1;

        oper_1 = s[i++];
    }
    printf("1. Operand_1 is now: %d\n", operand_1);
    // now operand_1 is complete, moving on to a continuos taking of operand_2:
        // Preparing for operand_2 loop:
    clear_whitespace(s, &i);
    operand_2 = str_to_int(s, &i);
    clear_whitespace(s, &i);

    //Endpoint 2:
    if (s[i] == 0){
        printf("1. (Returned) Operand_1 + Operand_2 is: %d\n", calc_duo_opers(operand_1, operand_2, oper_1));
        return calc_duo_opers(operand_1, operand_2, oper_1);
    }

    

    // main loop since operand_1. (after multi/divi eval seq of operand_2, operand_1 will now starting totaling the additions and subtractions)
    while (s[i] != 0){

        printf("2. Operand_2 loop beggining is: %d\n", operand_2);
        oper_2 = s[i++];
        // operand_2 loop
        while (oper_2 == '*' || oper_2 == '/'){
            clear_whitespace(s, &i);
            operand_3 = str_to_int(s, &i);
            operand_2 = calc_duo_opers(operand_2, operand_3, oper_2);
            printf("3. Operand_2 loop ending is: %d\n", operand_2);

            clear_whitespace(s, &i);

            if (s[i] == 0){
                printf("4. Reached end of arr during operand_2 eval; Sum of the operand_1: %d, Operand_2: %d with oper_1: %c is = %d\n", operand_1, operand_2, oper_1, calc_duo_opers(operand_1, operand_2, oper_1));
                // Endpoint 3:
                return calc_duo_opers(operand_1, operand_2, oper_1);
            }

            oper_2 = s[i++];
        }

        printf("4.(Near end of (s[i] == 0) loop) Operand_2 now is: %d\n", operand_2);
        // oper_2 now contains '+' or '-'

        printf("5. Sum of the operand_1: %d, Operand_2: %d with oper_1: %c is = %d\n", operand_1, operand_2, oper_1, calc_duo_opers(operand_1, operand_2, oper_1));
        operand_1 = calc_duo_opers(operand_1, operand_2, oper_1);
        oper_1 = oper_2;
        clear_whitespace(s, &i);
        operand_2 = str_to_int(s, &i);
        clear_whitespace(s, &i); // clearing for next iter s[i] eval (so skip oper_2 too)
        
    }

    // for the last eval upon reaching (s[i] == 0)
    operand_1 = calc_duo_opers(operand_1, operand_2, oper_1);
    
    //Final Endpoint (4):
    return operand_1;
}

int main(){
    char arr[] = " 1+2+3 "; //" 3*4/12 -5/2*4 - 34+ 24/12 ";
    //calculate(arr);
    printf("\nMain block print:\nOutput: %d\n\n", calculate((char *) arr));
    return 0;
}
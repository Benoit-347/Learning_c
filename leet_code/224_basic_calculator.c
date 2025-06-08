/*Given a string s representing a valid expression, implement a basic calculator to evaluate it, and return the result of the evaluation.


Example 1:

Input: s = "1 + 1"
Output: 2
Example 2:

Input: s = " 2-1 + 2 "
Output: 3
Example 3:

Input: s = "(1+(4+5+2)-3)+(6+8)"
Output: 23
*/

/* Using 3 fns:
    1) convert str to int: To pass arr and index from start of number; return int
    2) eval expr: a recursive fn, passing arr and index of the number that is right after parenthesis
    3) convert, the main fn
    
    Understanding the position of i at array and how it is maintained will red most tracing of logic in this porgram*/

#include <stdio.h>

// the i value will hold the index of the next element
int str_to_int(char * arr, int * i){    // pass str arr and the index starting from the str int
    int num = 0;
    char ch;
    while ( (ch = arr[*i]) >= '0' && ch <= '9'){
        num = num*10 + (ch - '0');
        (*i)++; // this fn wven when exit, will keep i val at next element's index
    }
    return num;
}

// when encounter '(', not changing i value, to be at val after '(' (since cur is in var ch)
int calc_exp(char * arr, int * i){
    int num, total = 0;
    char ch, flag_sign;

    while (arr[*i] == ' ')
       (*i)++;    // skip whitespaces 

                // the first char if a number must be copied.
    if (arr[*i] !='(')
        total = str_to_int(arr, i);

        // evaluates the exps and returns the total after reaching ')' (Note: i val is incr after loop end i.e. reaching ')' to keep i at new ele
    while ( (ch = arr[*i]) != ')' ){
                // printf("ch: %c\n", ch);
        (*i)++;
        if (ch == '+')
            flag_sign = 0;
        else if (ch == '-')
            flag_sign = 1;
        else if (ch >= '0' && ch <= '9'){
            (*i)--;     // passing str_to_int req i at int str element
            num = str_to_int(arr, i);   // i now back to next ele
                            //printf("The n: %d\nSign: %d\n\n", num, flag_sign);
            if (flag_sign == 0)
                total += num;
            else 
                total -= num;
        }
        else if (ch == '('){    
            num = calc_exp(arr, i); //recur starts (npw the current i is at ele after the ch), returns when this reaches a ')' and this one changes i to ele after ')'.
            if (flag_sign == 0)
                total += num;
            else 
                total -= num;
        }
        else if (ch == ' ')
            ;
        else 
            printf("Unidentified exp: '%c'\n", arr[--(*i)]);
    }
    (*i)++; // the part of fn that does all the ')' skipping to maintain next ele index throughout recurs.
    return total;
}

int calculate(char* s) {    
    int i = 0, total = 0, num;
    char ch, flag_sign;

    while (s[i] == ' ')
        i++;    // skip whitespace  
                // i here, acts as index for next element
    total = str_to_int(s, &i); // initializing starting number

    while ( (ch = s[i++] ) != 0){   // next number
        if (ch == '+')
            flag_sign = 0;  // indicates do addition
        else if (ch == '-')
            flag_sign = 1;  // indicates do subtraction
        else if ( ch >= '0' && ch <= '9'){
            --i;    // adjust i to give current index
            num = str_to_int(s, &i);
            if (flag_sign == 0)
                total += num;
            else
                total -= num;
            }
        else if (ch == ' ')
            ;
        else if (ch == '('){
            // keeping i at next element, number index
            num = calc_exp(s, &i);
            if (flag_sign == 0)
                total += num;
            else
                total -= num;
        }
        else{
            printf("Unidentified match: '%c'\n", ch);
            return 0;
        }
    }
    return total;
}

int main (){
    char arr[] = " 2-1 + 2";
    int num = 0;
    num = calculate(arr);
    printf("The number is %d\n", num);
}
/* This file will be compiled to have the code of 4 different files: 
    i) main.c controlling all operations
    ii) storage: all the vars
    iii) getop.c
    iv) get and unget so that we can later choose to use this or compile with library

    Notes:
        learnt imp lesson: static var is not available for linking hahaha (soln simply declare out of main i.e. global -> current file scope  but, available for linking as well)
                            to use extern each time a var/fn is being used by another file (for fns, it not neccessary for multiple use of extern if done in main once.  Raises warning tho ._.)
                                    why does mentioning only once work? -> Ans Since the functions can read from global, once extern is used, the external defined memory becomes accessible throughout that whole file.
                                        line2: So when all the fns are defined at operations area i.e. main, the fns interlink each other through scope of the current file's externs.
                                            line3: (the vars could also be done similarly by simply externing them once at current file's extern)

                                            static: provides private, permenent storage of identifiers; want to use multiple global vars but scared if extern conflicts with same names? Using static you can avoid scope issues while linking using extern.
from line3:
// Global variable declarations
    extern double my_stack[];
    extern int my_sp;
    extern double number;
    extern char buf[];
    extern int bufp;
                                            */

#include <stdio.h>

extern double number;
extern int push(double);    //can use # include calc.h instead
extern double pop();
extern int get_element();


/*workflow:
take an element from terminal;
match it to my symbols, according push number or pop and push computaion, or if '\n' print the value at pop()
    */
   int main(){
    int c;
    double op2;
    while((c = get_element()) != EOF){
        switch (c)
        {
        case '0':
            push(number);
            break;
        case '+':
            push(pop() + pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '*':
            push(pop() * pop());
            break;
        case '/':
            op2 = pop(); 
            push(pop() / op2);
            break;
        case '%':   // (exer 4.3)added feature of % operator (makes use of only int so doing type casting forced to int and push to double type)
            op2 = pop(); 
            push( (int) pop() % (int ) op2);
            break;

        case '\n':
            printf("Total: %f\n", pop());
            break;
        default:
            printf("None detected: %c\n", c);
            break;
        }
    }
    printf("Last element if stack was: %f\nExited program successfully\n", pop());  // exer 4.9 (requires better EOF handling as 2 EOFs req to exit rn)
    return 0;

}
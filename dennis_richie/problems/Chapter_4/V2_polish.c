#include <stdio.h>
/*
The explaination of the workflow of code for future reference:
aim: to make a simple calculator program by polish method ( 4 2 + 5 * = (4 + 2) * 5  )
method:
    1. Taking input from terminal directly (without making it modular by creating a arr and foramtting the arr to have calc formatted elements)
        one char at a time, 
    2. if input is number, continue to get number until not num, return num as int (singned float). Else return the char, also at beggining skip space.

        This works as this is made into a fn that is called each time an element is needed. Therefore at the start even the whitespace is skipped.
        features of this fn: accepts sign and even float
        Nested fns used:
            get_char and unget_char: makes use of common buffer which is in the global scope, used to put input data back in buffer (simulating it)
    3. In main fn, takes elements, (switch) if number push it, else  pop and calc it. If '\n' print the value at stack.
            
*/





// global variables     (global declarations)
# define MAXSIZE 100
static double my_stack[MAXSIZE];
static int my_sp = 0;
static double number;

// buffer
#define BUFFER_SIZE 20
char buf[BUFFER_SIZE];
int static bufp = 0;

// next 2 functions create own stack (arr) with a auto handled pointer, which creates a place to put back input (achived here by redirecting input)
int get_char(){
    return (bufp>0? buf[--bufp]: getchar());
}

int ungetchar(char c){
    buf[bufp++] = c;
}

// makes use of a custom global arr which stores elements
int push(double num){
    extern double my_stack[];
    extern int my_sp;
    my_stack[my_sp++] = num;
}

double pop(){
    double element = my_stack[--my_sp];
    return element;
}

// used to get a single entity here, being either number (neg or postive) or other.
// if its a number, create a repition custom to it alone, such that until the getchar in not int, it keeps taking num.
int get_element(){
    int ch;
    extern double number;
    int neg_flag = 1;
    number = 0;

    ch = get_char();

    while (ch == ' ')
            ch = get_char();
    
    if (ch == '-'){
        ch = get_char();
        if (ch >= '0' && ch <='9')
            neg_flag = -1;
        else{
            ungetchar(ch);
            ch = '-';
        }
    }
    if (ch >= '0' && ch <='9'){
        while(ch >= '0' && ch <='9'){
            number = number*10 + ch - '0';
            ch = get_char();
        }
        if (ch == '.'){
            int power = 1;
            ch = get_char();
            while(ch >= '0' && ch <='9'){
                number = number*10 + ch - '0';
                power *=10;
                ch = get_char();
            }
            number = number/power;
        }
        ungetchar(ch);
        number *= neg_flag;
        return '0';
    }
    else {
        return ch;
    }
}

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
        case '\n':
            printf("Total: %f\n", pop());
            break;
        default:
            printf("None detected: %c\n", c);
            break;
        }
    }

}

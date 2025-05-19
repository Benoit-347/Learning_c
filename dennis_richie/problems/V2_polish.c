#include <stdio.h>

// global variables     (global declarations)
# define MAXSIZE 100
static int my_stack[MAXSIZE];
static int my_sp = 0;
static int number;

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
int push(int num){
    extern int my_stack[];
    extern int my_sp;
    my_stack[my_sp++] = num;
}

int pop(){
    int element = my_stack[--my_sp];
    return element;
}

// used to get a single entity here, being either number (neg or postive) or other.
// if its a number, create a repition custom to it alone, such that until the getchar in not int, it keeps taking num.
int get_element(){
    int ch;
    extern int number;
    int neg_flag = 1;
    number = 0;

    ch = get_char();

    while (ch == ' ')
            ch = get_char();
    
    if (ch == '-'){
        ch = get_char();
        if (ch >= '0' && ch <='9')
            neg_flag = -1;
        else
            ungetchar(ch);
    }
    if (ch >= '0' && ch <='9'){
        while(ch >= '0' && ch <='9'){
            number = number*10 + ch - '0';
            ch = get_char();
        }
        number *= neg_flag;
        ungetchar(ch);
        return '0';
    }
    else {
        return ch;
    }
}

// workflow:
int main(){
    int c, op2;
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
            printf("Total: %d\n", pop());
            break;
        default:
            printf("None detected\n");
            break;
        }
    }

}
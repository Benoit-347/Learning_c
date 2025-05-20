#include <stdio.h>

// global variables     (global declarations)
# define MAXSIZE 100
static double my_stack[MAXSIZE];
static int my_sp = 0;
static double number;


// makes use of a custom global arr which stores elements
int push(double num){
    extern double my_stack[];
    extern int my_sp;
    my_stack[my_sp++] = num;
    return 0;
}

double pop(){
    double element = my_stack[--my_sp];
    return element;
}


int * get_line(){
    static int arr[MAXSIZE];
    int i;
    for(i = 0; i<MAXSIZE-1 && ((arr[i] = getchar()) != EOF); i++){
        ;
    }
    arr[i] = 0;
    return arr;
}

int get_element(){
    
}

/*workflow:
take an element from terminal;
match it to my symbols, according push number or pop and push computaion, or if '\n' print the value at pop()
    */

int main(){
    int c;
    double op2;
    int * arr = get_line();

    while((c = get_element(arr)) != EOF){
        switch (c)
        {
        case '0':
            push(number);
            number = 0;
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

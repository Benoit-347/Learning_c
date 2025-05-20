#include <stdio.h>

// global variables     (global declarations)
# define MAXSIZE 100
static double my_stack[MAXSIZE];
static int my_sp = 0;
static double number;

//get_line:
static char arr[MAXSIZE];
static int i = 0;

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


char * get_line(){
    extern char arr[];
    int j;
    for(j = 0; j<MAXSIZE-1 && ((arr[j] = getchar()) != EOF); j++){
        ;
    }
    arr[j] = 0;
    return arr;
}

int get_element(){
    extern int i;
    extern char arr[];
    extern double number;
    int ch, neg_flag = 1, power = 1;
    //skipping spaces
    for (; (ch = arr[i]) == ' ';i++)
        ;

    //sign
    if ( ch == '-' && (arr[i+1] >='0' && arr[i+1] <= '9') ) {
        neg_flag = -1;
        i++;
    }

    if (ch >= '0' && ch <= '9'){
        for (; ( ( (ch = arr[i]) != 0 ) && (ch >= '0' && ch <= '9') );i++)
                number = number*10 + ch - '0';
    
        if (ch == '.'){
            i++;
            for (; ( ( (ch = arr[i]) != 0 ) && (ch >= '0' && ch <= '9') );i++){
                number = number*10 + ch - '0';
                power *= 10;
            }
            number = number / power;
        }
        else
            i--;
        number *= neg_flag;
        return '0';
    }
    else
        return ch;
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

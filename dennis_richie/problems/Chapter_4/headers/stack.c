
# define MAXSIZE 100
double my_stack[MAXSIZE];
int my_sp = 0;
double number;

// buffer
#define BUFFER_SIZE 20
char buf[BUFFER_SIZE];
int bufp = 0;


// makes use of a custom global arr which stores elements
int push(double num){
    extern double my_stack[];
    extern int my_sp;
    my_stack[my_sp++] = num;
    return 0;
}

double pop(){
    extern double my_stack[];
    extern int my_sp;
    double element = my_stack[--my_sp];
    return element;
}
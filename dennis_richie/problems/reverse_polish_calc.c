#include <stdio.h>

// global variables     (global declarations)
# define MAXSIZE 100
static int my_stack[MAXSIZE];
static int my_sp = 0;


int push(int num){
    extern int my_stack[];
    extern int my_sp;
    my_stack[my_sp++] = num;
}

int pop(){
    int element = my_stack[--my_sp];
    return element;
}

int main(){
    push(40);
    printf("%d\n", my_stack[my_sp -1]);
    printf("%d\n", pop());
}
#include <stdio.h>

// next 2 functions create own stack (arr) with a auto handled pointer, which creates a place to put back input (achived here by redirecting input)
int get_char(){
    extern char buf[];
    extern int bufp;
    return (bufp>0? buf[--bufp]: getchar()); 
}   // only 1 max: return (bufp>0? buf[--bufp]: getchar()); (exer 4.8)

int ungetchar(char c){
    extern char buf[];
    extern int bufp;
    buf[bufp++] = c;
    return 0;
}   // only 1 max: buf[0] = c; bufp = 1;
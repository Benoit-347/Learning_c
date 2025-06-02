// consider a program to copy a string from s to t.

#include <stdio.h>

// using pointer subscripting:
void strcpy(char *t, char *s){
    int i = 0;
    while ((t[i] = s[i]) != 0)
        i++;
}

// using pointers :
void strcpy(char *t, char *s){
    while ((*t = *s) != 0)
        t++;
        s++;
}

// experienced programmers prefer this method:
void strcpy(char *t, char *s){
    while (*t++ = *s++)     // removed cmp with 0 as return value of assignment would also be 0.
        ;
}
// Note: The last 2 methods are more efficient as it avoids the need for an additional variable (i) and uses pointer arithmetic directly.
// similar to the getline fn, we have fgets. here taking n char inputs and putting it onto a ptr location specified in argument.

# include <stdio.h>

char * fgets(char *s, int n, FILE * iop){
    register int c;
    register char *cs; // char var "cs", to copy the ptr at argument.

    cs = s;
            // take input as long as 1.max not reached and 2.input is not EOF
    while (--n > 0 && (c = getc(iop)) != EOF)  // --n as we need 1 extra char space at end for \0.
        if ((*cs++ = c) == '\n')    // copy input to string arr, and end input when encouter '\n'. (it also includes \n into the output string of getling).
            break;
    
    *cs = 0;
    return (c == EOF && cs == s) ? NULL : s;    // if string in empty and the last input is EOF, reutrn NULL, else return ptr to the same char ptr, passed at argument.
}

int fputs(char * s, FILE * iop){
    int c;
    
    while (c = *s++)    // until NULL is encountered, keep writing chars into FILE ptr, which was passed as arg.
        putc(c, iop);
    
    return ferror(iop) ? EOF : 0;
}

int getline(char * line, int max){
    if (fgets(line, max, stdin) == NULL)    // when no input was given due to first input being EOF
        return 0;           // do note that fgets returns the same ptr line back, as the arg we passed.
    
        return strlen(line);
}
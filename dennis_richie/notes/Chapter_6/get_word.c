# include <stdio.h>

// next 2 functions create own stack (arr) with a auto handled pointer, which creates a place to put back input (achived here by redirecting input)
// buffer
#define BUFFER_SIZE 20
char buf[BUFFER_SIZE];
int bufp = 0;

int getch(){
    extern char buf[];
    extern int bufp;
    return (bufp>0? buf[--bufp]: getchar()); 
}   // only 1 max: return (bufp>0? buf[--bufp]: getchar()); (exer 4.8)

void ungetch(char c){
    extern char buf[];
    extern int bufp;
    buf[bufp++] = c;
}   // only 1 max: buf[0] = c; bufp = 1;

// prog to take a word, keeping extra char at buffer (buffer used only whn taking input during a alpha_num start of word (3rd if inside begginging of for loop) ).
// take input to first pos w, if not EOF, thn if its whitespace, return it, else run a loop geting ch, until a non alpha_num encounted (in which case put it back into the buffer). And at end always retuns the fist val at arr w (if no valid data, returns 0)
int getword(char *word, int lim){
    int c, getch(void);
    void ungetch(char);
    char *w = word; // copying the ptr to another var for faster transfer to dereferce ig

    while ( isspace(c = getch()) )
        ;
    if (c != EOF)
        *w++ = c;   // (includes any alpha_num char) && keeping the whitespace char also, as whn returning c, the data is still stored at w
    
    if (!isalpha(c)){   // if not a aphabet, put 0 to existing arr w, then pass obatined c to return.
        *w = 0;
        return c;
    }

    for (; --lim > 0; w++){
        if ( !isalnum(*w = getch()) ){  // assign to arr w getch, then chk if its alpha or int, else ungetch and break.
            ungetch(*w);
            break;
        }
    }
    *w = 0;
    return word[0]; // the val taken at beggining non EOF getch
}
// program to count the number of each unique word from a list of words
    // uses a struct containing 2 members: a (word) str ptr and a (count) int

# include <stdio.h>

struct key{
    char *word;
    int count; 
};

struct key keytab[] = {"auto", 0,
                    "break", 0,
                    "case", 0,
                    "char", 0,
                    "const", 0,
                    "continue", 0,
                    "default", 0,
                    "unsigned", 0,
                    "void", 0,
                    "volatile", 0,
                    "while", 0
                    };
// prog to take a word, keeping extra char at buffer (buffer used only whn taking input during a alpha_num start of word (3rd if inside begginging of for loop) ).
// take input to first pos w, if not EOF, thn if its whitespace, return it, else run a loop geting ch, until a non alpha_num encounted (in which case put it back into the buffer). And at end always retuns the fist val at arr w (if no valid data, returns 0)
int getword(char *word, int lim){
    int c, getch(void);
    void ungetch(int);
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


int main(){

}
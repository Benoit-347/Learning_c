// program to count the number of each unique word from a list of words
    // uses a struct containing 2 members: a (word) str ptr and a (count) int

# include <stdio.h>
# include <ctype.h>
# include <string.h>
# define MAXWORD 100


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

// binary search fn on struct arr tab, by the words inside key.word
struct key * binary_search(char * word, struct key * tab, int n){
    struct key * low = tab;
    struct key * high = tab + n;
    struct key * mid;

    while (low < high){
        mid = low + (high - low)/2;     // pointer subtraction to find int difference first, then add to ptr low

        int result = strcmp(word, mid -> word); // alternative *(mid).word

        if (result == 0)
            return mid;
        else if (result < 0)
            high = mid;
        else
            low = mid +1;
    }

}


# define MAX_WORD_SIZE 100
int main(){

    int count = sizeof(keytab) / sizeof(keytab[0]);
    
    /*
    testing binary search
    int pos = binary_search("break", keytab, sizeof(keytab)/sizeof(keytab[0])) - keytab;
    printf("Found string at pos %d\n", pos);
    */

    char input_word[MAX_WORD_SIZE];
    struct key * ptr_to_struct;

    while (getword(input_word, MAX_WORD_SIZE) != EOF){
        ptr_to_struct = binary_search(input_word, keytab, count); // add additional line above this statement with if conditions to filter to allow seach on only aphabet chars in word arr.
        printf("Returned: %d\n", ptr_to_struct - keytab);
    }
    return 0;
}
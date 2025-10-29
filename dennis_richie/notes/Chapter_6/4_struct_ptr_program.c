// program to count the number of each unique word from a list of words
    // uses a struct containing 2 members: a (word) str ptr and a (count) int
        // creates a initial arr of struct, and the structs are arranged in the arr, such that the word member is sorted wrt struct_arr.
            // we take words until a EOF is reached and on each pass of input word, we search and update the respective struct word value.

// skip to line 58 for binary search customized to our struct, line 87 for main

# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include "get_word.c"

int getword(char *word, int lim);

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

    return 0;
}

    /*
    testing binary search
    int pos = binary_search("break", keytab, sizeof(keytab)/sizeof(keytab[0])) - keytab;
    printf("Found string at pos %d\n", pos);
    */

# define MAX_WORD_SIZE 100
    // take word input, match word with struct arr's word member. Add count of the same member. Print the counts at the end.
int main(){

    int count = sizeof(keytab) / sizeof(keytab[0]);
    char input_word[MAX_WORD_SIZE];
    struct key * ptr_to_struct;

    while (getword(input_word, MAX_WORD_SIZE) != EOF){  //input
        
        ptr_to_struct = binary_search(input_word, keytab, count); // search and result // add additional line above this statement with if conditions to filter to allow seach on only aphabet chars in word arr.
        
        if ( (!ptr_to_struct) )
            ptr_to_struct -> count++;   // if result was successful
        else
            printf("Not detected %s\n", input_word);
    }

    // printing output
    for (ptr_to_struct = keytab; ptr_to_struct < keytab + count; ptr_to_struct++)
        if ( (ptr_to_struct -> count) )    // skipping 0 count structs
            printf("%3d \t %s\n", ptr_to_struct -> count, ptr_to_struct -> word);
    return 0;
}
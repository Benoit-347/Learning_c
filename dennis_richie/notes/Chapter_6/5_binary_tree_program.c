# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include "get_word.c"

int getword(char *, int);

// eacn individual struct
struct node {
    char * word;
    int count;
    struct node * left;
    struct node * right;
};


// when using fns, to create a new struct (and be usable in main scope && hence be usable in the chains by being able to reference it using ptr) if a struct with existing word does not exist.
struct node * s_alloc(void){
    return (struct node *) malloc(sizeof(struct node));
}

int result;

// the main fn that will maintain and insert to binary tree
struct node * addtree(struct node * p, char * word){
    
    // the KEY and foundational condition of our function.      Every null struct ptr in a node will go through this fn to be a new node; i.e. every new word that has no existing node with its id/ word string, will go thorugh this condition to become a new node.
    if (p == 0){    
        p = s_alloc();  // allocate storage and ret struct ptr to storage
        p -> word = strdup(word);   // strdup 1. allocates mem for the char arr 2. copies the arr to new allocated mem. 3. returns ptr
        p -> count = 1;
        p -> left = 0;
        p -> right = 0;
                        // return p; anyways this code falls back to after else
    }
    else if ( (result = strcmp(word, p -> word)) > 0 )
        addtree(p -> right, word);
    else if (result < 0)
        addtree(p -> left, word);
    else
        p -> count++;
    return p;
}

int main(){
    struct node * p = 0;
    char * input_word;
    while ( (getword(input_word, 100) != EOF) )
        printf( "Value: \t%s \t count: \t %d\n", input_word, addtree(p, input_word) -> count);

    return 0;
}
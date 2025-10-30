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
        p -> right = addtree(p -> right, word);
    else if (result < 0)
         p -> left = addtree(p -> left, word);
    else{
        p -> count++;
        printf("New count of %s is: %d\n", p-> word, p -> count);
    }
    return p;
}

// program ends if passed parameter p is null, else, go to leftmost sequence until null, then return back.. and whn back  continue to print the next instruction (print cur node) then again chain to right most of cur node (the one before leftmost null) and thn 1 step back and print cur node, doing this to every node withing 1st nest, completes first leftmost node, then this keeps going until rightmost node is reached, (rightmost NULL is the end cond now)
void treeprint(struct node * p){
    if (p){
        treeprint(p -> left);
        printf("Word %s appeared %d times\n", p -> word, p -> count);
        treeprint(p -> right);
    }
}

int main(){
    struct node * p = 0;
    char input_word[100];
    while ( (getword(input_word, 100) != EOF) )
        p = addtree(p, input_word);
    
    printf("\n---FINAL OUTPUT---\n");
    treeprint(p);   // does a recursive print starting from the left most node of root struct, towards the right most from the leftmost branch. (the right most starting node will be later than the leftmost nested most node)
    return 0;
}
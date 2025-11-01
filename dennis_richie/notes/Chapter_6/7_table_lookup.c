// a lookup table is used in C to search and obtain items (like preprocessor directive of #define, to replace certian text to another) in avg O(1) time, worst case (with collisions) O(n) time
    /* 3 tpyes of loopup
        1. arr
        2. binary tree
        3. hash map

        Hash Table lookup:
        Uses array of ptrs to structures  (also called Linked lists)

        Each struct contains:
            1. a member for  word => ptr to char
            2. a pair to first member ( 2nd word)
            3. ptr to next struct at same index of main arr

            The irst node at this index is called head node which is a ptr ofc) and each of these structs hold a member with a ptr to another struct, each ptr holding 1 struct adr. This members in each struct creates chain for successive nodes which had arrived at the same index of a hashtable.

            Note: hashtables are not structs themselves but, array of pointers to structs,  Because:
                The array itself lives on the stack (or global data segment)
                The structs (nodes) live on the heap, dynamically allocated via malloc
                The pointers in the hash table array link these two worlds.

            note: <datatype> ptrs in the hashtable == ptrs stored for chaining in each struct.

            Are all table lookups a hashmap?

                🚫 Not necessarily — “table lookup” is a broader concept.


                Let’s classify:
                | Lookup Type                       | Underlying Structure        | Example                         | Notes                                |
                | --------------------------------- | --------------------------- | ------------------------------- | ------------------------------------ |
                | *Direct table lookup*             | Simple array                | int table[256]                  | Uses index directly (no hash, O(1))  |
                | *Hash table lookup*               | Array of pointers to chains | struct entry *table[HASHSIZE]   | Uses hash function (O(1) average)    |
                | *Binary search table lookup*      | Sorted array or tree        | bsearch() or BST                | O(log n) lookup, maintains order     |
                | *Jump tables / function tables*   | Array of function pointers  | CPU dispatch tables             | Used for switch-case or opcode jumps |
        
    */

// CODE
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define HASHSIZE 101

// conv word to int
unsigned int hash(char * word){
    char * temp = word;
    char ele = *word++;
    unsigned int result = 0;
    while (ele){
        result = result*31 + ele;
        ele = *word++;
    }

    printf("Hashed %s to %d\n", temp, result % 101);
    return result % 101;    // This produces the starting pos in an hastab arr
}

// create a struct having word and ability to hold chain of same pos structs.
struct node{
    char * word;
    char * replacement_word;
    struct node * next;
};

// fn to insert structs to an arr, by passing ptrs to arr to preserve memory and insertion time, and dynamic-ness.
void insert(struct node ** hastab, char * word){
    unsigned int ele = hash(word);
    struct node * struct_ptr = malloc(sizeof(struct node));
    struct_ptr -> word = strdup(word);
    struct_ptr->next = NULL;


    struct node * cur_ptr;
    cur_ptr = *(hastab + ele);
    if ( cur_ptr ){
        printf("Copy exists! Moving ahead at index %d to next node at chain\n", ele);
        while (cur_ptr -> next){
            printf("Copy exists! Moving ahead at index %d to next node at chain\n", ele);
            cur_ptr = cur_ptr -> next;
        }
        cur_ptr -> next = struct_ptr;
    }
    else
        *(hastab + ele) = struct_ptr;
}

// search all chains at offset of hastmap, i.e. index
int search(struct node ** hashmap, char * word){
    unsigned int ele = hash(word);
    struct node * cur_ptr;
    cur_ptr = *(hashmap + ele);
    while ( cur_ptr ){
        if ( !strcmp(word, cur_ptr -> word))
            return 1;
        else
            cur_ptr = cur_ptr -> next;
    }

    return 0;
}

int main(){
    struct node * hashtab[HASHSIZE] = {0};
    char word1[] = "GUB";
    char word2[] = "CUB";
    char word3[] = "GUB";

    insert(hashtab, word1);
    insert(hashtab, word2);
    insert(hashtab, word3);

    if ( search(hashtab, word1) )
        printf("Found word: %s\n", word1);
    return 0;
}
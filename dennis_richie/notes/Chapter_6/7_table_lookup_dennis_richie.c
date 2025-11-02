# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <time.h>

struct node{
    char * word;
    char * replacement_word;
    struct node * next;
};

# define HASHSIZE 101

struct node * hashtab[HASHSIZE];

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



struct node * lookup(char *s){
    struct node * node_ptr;

    // this for loop is the STANDARD IDIOM for walking along a linked list:
        // initial: (assign var to ) head_ptr
        // if var not NULL, (assign var to) (*head_ptr).next => repeat
        // for (ptr = head; ptr !=  0; ptr = ptr -> next
            // ...
    for (node_ptr = hashtab[hash(s)]; node_ptr != 0; node_ptr = node_ptr -> next)
        if ( strcmp(s, node_ptr -> word) == 0 )
            return node_ptr;
        // else do nothing, skip to next loop
    return 0;
}

// install uses loopup to search if name being installed is already present (if yes, rewrite the replacement word), else add new, at a null loc.

struct node * insert(char *name, char * defn){
    struct node * cur_ptr;
    
    if ( cur_ptr = lookup(name) ){
        free(cur_ptr -> replacement_word);
        cur_ptr->replacement_word = strdup(defn);   // chk if error in returning strup, as lack of mem by returning 0.
    }
    else{
        int ele = hash(name);
        cur_ptr = malloc(sizeof(struct node));
        cur_ptr -> word = strdup(name);
        cur_ptr -> replacement_word = strdup(defn);

        // 2 types to insert: at head and at tail-
        // Head Insertion
        // Assign the new node to the head node after copying old head node to the new node first.
            // why head insertion is almost ALWAYS  better: faster insert, maintain recency, smaller code

        cur_ptr -> next = *(hashtab + ele);
        *(hashtab + ele) = cur_ptr;


        // Tail insertion
        // Last node, next is assigned the ptr to new node
            // why tail may be needed: maintain queue type order- You plan to iterate over elements in the order they were added.
        
        /*
        cur_ptr = *(hashtab + ele);
        if (cur_ptr ) {       // if hastab[index] already taken by a ptr
            while (cur_ptr -> next)
                cur_ptr = cur_ptr -> next;
        cur_ptr = cur_ptr -> next = malloc(sizeof(struct node));
        cur_ptr -> word = strdup(name);
        cur_ptr -> replacement_word = strdup(defn);
        }
        else{
            cur_ptr = malloc(sizeof(struct node));
            cur_ptr -> word = strdup(name);
            cur_ptr -> replacement_word = strdup(defn);
            cur_ptr -> next = 0;
            *(hashtab + ele) = cur_ptr;
        }
        */

    }

    return cur_ptr;
}

int main(){

    clock_t start = clock();  // clock() => the number of CPU clock ticks that have elapsed since the start of your program.
                                // CLOCKS_PER_SEC => number of clocks per second, i.e. 1/CLOCKS_PER_SEC is amount of time per clock.
    struct node * temp_ptr;
    
    temp_ptr = insert("hello", "hi");
    printf("Origianl text: %s \t, replacement text: %s\n", temp_ptr -> word, temp_ptr -> replacement_word);
    temp_ptr = lookup("hello");
    printf("Origianl text: %s \t, replacement text: %s\n", temp_ptr -> word, temp_ptr -> replacement_word);
    temp_ptr = insert("abt", "b");
    printf("Origianl text: %s \t, replacement text: %s\n", temp_ptr -> word, temp_ptr -> replacement_word);
    temp_ptr = lookup("abt");
    printf("Origianl text: %s \t, replacement text: %s\n", temp_ptr -> word, temp_ptr -> replacement_word);
    
    // use fn sprintf(<variable> <replacement text>) => replaces a var with a string like text word<i> with word%d. Combine with a for loop to automate code lines for multiple inserts.
        // sprintf(name, "word%d", i);
    for (int i = 0; i< 1000; i++){
        char name[100], defn[100];
        sprintf(name, "word_%d", i);
        sprintf(defn, "defn_%d", i);
        temp_ptr = insert(name, defn);
        printf("Origianl text: %s \t, replacement text: %s\n", temp_ptr -> word, temp_ptr -> replacement_word);
        temp_ptr = lookup(name);
        printf("Origianl text: %s \t, replacement text: %s\n", temp_ptr -> word, temp_ptr -> replacement_word);
    }

    clock_t end = clock();

    printf("Runtime: %.3f ms\n", (double) (end - start)*1000/CLOCKS_PER_SEC);
    return 0;

}


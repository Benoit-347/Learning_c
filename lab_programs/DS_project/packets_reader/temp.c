# include <stdio.h>

struct {        // the struct here is called anonymouse struct (you cannot create another obj with same struct) Note: What i call obj's are also called variables in C
    int a;
    int b;
    int c;
} A;
// creates a object A with temporary struct

typedef struct {    // the struct here is also called anonymouse struct
    int a;
    int b;
    int c;
} B;        // creates a typdedef name 'B'
// creates a typedef B (similar to the struct name itself being B, but No the struct is anonyomous and this is typdef), with feature of not putting prefix 'struct' on obj creation. 


// this showcases the distinction of our above struct declarations

typedef struct Node{    // THis adds 'Node' to the namespace of struct type
    int a;
    int b;
    int c;
} Node;     // This adds 'Node' to the namespace of typedef type
//Hence both struct Node A; && Node A; produce an equivalent obj. (But the creation stage differs wrt one from struct and other from typedef)

// why 2 ways to do same thing? Because we need struct's namespace to allow self referential pointer within struct body. And the feature of not using 'struct' prefix hence adding this to typedef namespace.
    // Hence double declaration, each being in seperate namespace; and Not Colliding.



int main(){
    A.a = 10;
    printf("The value at A.a is: %d\n", A.a);
    B b;
    b.a = 20;
    printf("The value at b.a is: %d\n", b.a);


    printf("\nUsing Namespace of 'struct':\n");
    struct Node C;
    C.a = 100;
    printf("The value at C.a is: %d\n", C.a);
    
    printf("Using Namespace of 'typedef': \n");
    Node D;
    D.a = 200;
    printf("The value at D.a is: %d\n", D.a);

    return 0;
}
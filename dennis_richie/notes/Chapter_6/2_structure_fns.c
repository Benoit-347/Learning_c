// the comiler makes available to copy blocks of memory of structures by copying mechanism in C (syn by copying one struct obj_name to another stuct_obj name)
    // it copies all the members of obj_1 to obj_2 of same struct type.


/*
Structures:
They are in memory just range of memory,
the different elements are made known at compiler time by the descripter table, it keeps metadata of the offset of each member in struct.
On compilation all tokens refering to members is replaced with this direct arr-indexing method with the struct obj as the starting loc. (hence, structures being very similar to arrs, with added feature of copying all members with one line (maybe simliar to memcpy))*/
    // it matches to the descriptor symbol table during compilation, and does no symbol table matching during runtime.

// legals operation of functions on structures are:
    // i) copying a struct
    // ii) taking its address with '&' operator
    // iii) accessing its members

//program 1:
    // to create a complete struct by a) creating struct obj,  passing its members to a fn, fn creates temp struct, return + assign combo -> copies entire struct to obj in main fn.
        // takes advantage of coping feature of struct objects. (showcased at temp_1, temp_2 variables specifically)
# include <stdio.h>

struct point { int x; int y; } temp_1, temp_2;

/*
// IGNORE
temp_1 = {5, 7};   *WRONG* In C, executable statements like assignment (=) must be inside a function, such as main(), to run.
temp_2 = temp_1;
*/

struct point fn_return_point_obj(int x, int y){
    struct point temp;  // creates a temporary local struct obj wit point obj type
    temp.x = x;
    temp.y = y;

    return temp;    // to later copy from this to another abj
}

int main(){
    
    // IGNORE
    // copying mechanism showcase
    // temp_1 = {5, 10}; *WRONG* feature of passing values as expression '{ }' is only available during initialization
    temp_1.x = 5;
    temp_1.y = 10;
    temp_2 = temp_1;
    printf("The obj temp_2 also has \nmember 'x' has value: %d\nmember 'y' has value: %d\n", temp_2.x, temp_2.y);

    // fn code
    struct point pt_1;
    pt_1 = fn_return_point_obj(10, 20); // copies from local to obj pt_1 in here (main)
    struct point pt_2;
    pt_2 = fn_return_point_obj(30, 40);
    printf("The obj pt_1 has \nmember 'x' has value: %d\nmember 'y' has value: %d\n", pt_1.x, pt_1.y);
    printf("\nThe obj pt_2 has \nmember 'x' has value: %d\nmember 'y' has value: %d\n", pt_2.x, pt_2.y);

    return 0;
}
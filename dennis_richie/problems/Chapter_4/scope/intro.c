// scope are of automatic < local < file (glabal)               # local/automaic: defined within a block
//              stack    stack   bss         dynamic types like malloc use heap

/* Notes:
    after C99 global (extern type) and local values of a variable can exist such that during the life of local, the global is shadowed */



// use extern to declare the identifier to be defined thoughout the file (extern, does not create nor initialize memory)
    
/*
note that this is invalid:

for (int i = 0; i<10; i++)
    extern int i;

 as i in declared within a function

    or its invalid even if declaring i in main then doing extern, 
    as main has its variables in the main block (therefore local) */

// THEREFORE "EXTERN" USE CASE: To link external varibles, the identifiers defined at memory can be made available to current scope (i.e the current file too)


//PROGRAM STARTS HERE

#include <stdio.h>  // 1 way i am trying is compiling file 1 and 2 with this one
                    // alternate: #include "file1.c"    even better: use header files ->  .h   #drawback of normal file is higher file size to object during compilation and compilation time.
extern int i;

int main(){
    printf("i with extern is: %d\n", i);
    return 0;
}

/*
I tried compiling multiple files and found out: compiling multiple files is similar to running the code of file 1 in current file,
so def of main in file 1 will conflict in file current.
Therefore treat them as storage/ extern files rather than normal files.
*/
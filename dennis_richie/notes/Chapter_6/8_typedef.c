// it makes creating user defined data types (and infns return type/ declaration) NOT require a prefix keyword like 'struct' / 'typedef'.
    // it is a compiler job. (not a preprocessor job, but it does so at compilation, semantically) It also can be used as a feature similar to # defineand is similar in fn to # define, tht it replaces text more complexly, beyond the scope of a # define.
        // IMP: its beyond avoiding struct keyword for structs, it is not only made for structs (which are pointers with offset matching, matched at compile time)
            // it helps make a data type witout need for a ptr.
                

# include <stdio.h>

//eg typedef long Counter;
typedef long type_1;

// ptr to fn 
typedef int (*CompareFn)(char *, char *);
        
type_1 var_a = 10;

CompareFn fn_1, strcmp;
// use case: when declaring data types (like int) in different computers, the size may vary affecting program reliability. Hence why using typdef, we can only insert/change the typdef, not needing to manually change each declaration.
        
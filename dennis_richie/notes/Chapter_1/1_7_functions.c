// functions are collections of a set of instructions to be executed, that does the whole work within its seperate own space (local memory)
    // i.e A reuseable block of code, encapsulates a set of instructions, under nicie of to perform a well defined task, within its own scope!
// functions when declared have their names and type of return and parameters it uses- made known to the compiler.
    // In a C program its a system that forwards to itself the neccessary data through parameters and does operations to it and outputs a single variable sized data. (might be a location holder instead i.e. pointer, to denote location to a sequence of outputs)
        // fn note: it cannot access other local scopes and can only do so by using pointers; it can only access its local scope and global variables and stuff like other compiler global things like fns
// call by value vs reference (i.e. using a local copy and performing operations on it and returning the result or doing operations on a data unit accessed manually by a pointer variable)
    // storage  local var -> size of data (1 - 16 bytes)         pointer -> 8 bytes
    // accessing -> std variable i.e. symbol table (1-3 cycles), pointers -> 1 extra step of dereferencing i.e.if cache miss ~100 cycles due to ram dereferncing, or ~(1-3) + ~(1-3)
        // but when return in same variable, local -> cpy to main var, ptr -> change already done, although this also req ram dereferencing ( can also use cache by using dirty cache process whr when cache is updated, later the RAM is also updated. so cycles on cache hit ~(1-3))
    // it seems you also need to declare a external varibale inside a local scope to make use of it.

// arrays -> they return a storage lacion, base location. And its elements accessed by moving accross base loction and dereferencing to obtain the data of the sequnce. char * ptr = {1, 2, 3, 4};
    // strings -> a niche of arr that hold a seq of elements that are 1 byte and also end with last element as 0 to denote end.


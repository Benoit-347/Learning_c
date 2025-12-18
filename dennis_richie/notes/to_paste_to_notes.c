// in c the data segment in static allocated, once compiled the data (especially stack; used in main and other fns) segment remains fixed limit.
    // By using sys calls, we can use dynamic memory allocation calls from stdlib, using malloc, to use space in bss segment.

// The main program's variable and array declarations create space in data/stack segment; this is fixed (compilation finds all declaration and makes a var table, along with space req)
// Then when calling fns, fns itself may contain variable declarations and arrays.
    // This space is also created each time a fn is called; So is a fn creating a new program unit each time?; Fns Also make use of stack, hence fns may be one single code with main program, with brach staments (and stack frame creation) when fn call is observed. 
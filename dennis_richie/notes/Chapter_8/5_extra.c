/*
Structs are just 1D arrays,
but 1D arrays require specifying index 0, 2 for each element.
Structs use names for position, and this is reduces back to 1D arr after compilation, with instruction only specifying access data type and offset from base addr
Now consider writing a multi datatype data collection, u may need multiple arrays for each datatype, or
                                                                                                    in ur program create mata data with prefixing fetch and push, to a mixed datatype arr (void *)

is this a 2 times derefence arr?
struct FILE _iob[20];
    it is compiled to a 1D arr, since any struct is a 1D arr _iob[0] is also a 1D;
        an arr[20][10]; is translated to 1D arr after compilation.
            Hence struct FILE _iob[20]; is basically arr[20][5] a 1D array.

Structs make data handling very classic and easy, as all data conversions for arr offset is handled by compiler.
Consider how many times you would need to manually write asm code for a multi data type arr.
            */
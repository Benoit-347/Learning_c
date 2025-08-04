/* Aim is to merge contents of one file into main file:
    2 methods: i) # include file_1.c ii) gcc file_main.c file_1.c

        Result: Both the methods result in an executable having same exe content.
            Difference: Compilation process- While at include the complition does one object, one assembly, one translation unit into one executale
                                             whereas, at multi-file compilation, multiple object, assemble and translation unit into one executable 

                                             Recommended: optimal to use header files by .h extension- does not re-copy unnessary code elements
                                            Else: Recommended to still use #include to reduce comp time (single pipeline)
                                                Nuance: modularity for very large projects - terminal multi file compilation
                                                */
# include "defining.c"  // Use <> for including files at the standard library path only, or "" for first checking dir of source file then to default implementation path.
    // or gcc file_main.c file_1.c -o temp.exe
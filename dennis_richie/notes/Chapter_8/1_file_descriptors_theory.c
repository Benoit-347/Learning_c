// the UNIX OS provides fns from the os though sys calls. 
// this chapter describes how to use most of these sys calls.
    // useful as ANSCI C library is models on UNIX facilities.
// 3 parts to this chapter: // 1. UNIX input output
                            // 2. UNIX file system
                            // 3. UNIX storage allocation

// ch 1- file descriptors.
    // in the UNIX OS all input and output are done through writing through files, even all peripheral devices (even keyboard and the screen) are files in the file system. 
    // before any writing, you must inform the system, by opening a file.
        // the sys checks your right to do so.
            // if all is well, the sys returns a non negative integer (called file descriptor).
            // this file descriptor (the non -ve int) is anologous to the file ptr, used to identity the file.
            // all info of an open file is maintained by the system.
                // hence any user program refers to a file only by the file descriptor.
    
// this file-descriptor table is managed by an Indexed array, in the process control block (PCB), where Each process has its own descriptor table.

    // since input and output involving keyboard and screen is so common, special arrangements made-
        // when the command interpreter (the "shell") runs a program file descriptors 0, 1 and 2 are open (representing stdin, stdout, stderr)
        // you can also redirect input or ouput using the '>' or '<' command.
        // eg- " prog < infile > outfile "
        // backend:     
        /*
            close(0);   // closes file descriptor 0 (stdin)
            open("infile", O_RDONLY);   // fd 0 now points to infile
            close(1);   // closes file descriptor 1 (stdout)
            open("outfile", O_WRONLY|O_CREAT|O_TRUNC);
        */
        // the program uses file 0 for input and 1 && 2 for output, it does not know whn the shell changes the file assignment, regarding where the input comes from, or the output goes.

    /*
    | Level             | Functions                                       | Buffered?                 | Unit   |
    | ----------------- | ----------------------------------------------- | ------------------------- | ------ |
    | **C stdio**       | `fopen`, `fclose`, `fread`, `fwrite`, `fprintf` | ✅ Yes (user-space buffer) | FILE*  |
    | **UNIX syscalls** | `open`, `close`, `read`, `write`, `lseek`       | ❌ No                      | int fd |

    */
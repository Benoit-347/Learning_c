// "cat" a utility command of unix, which is actually a program that reads a file and displays its contents onto the terminal.

// Reading/Writing a file

    // to do any operations onto a file, it must first be "opened" by a library function "fopen". This keyword fopen negotiates with the operating system; and returns a pointer, which can be used for multiple reads/writes.
        
        /* 
        START FOPEN EXPLAINATION
        fopen:
            

            1. When you call fopen("data.txt", "r"):   // C library (libc layer)

                (a) Argument parsing
                "data.txt" is passed (string as a pointer), "r" is parsed → library sets mode flags:

                (b) FILE structure creation
                fopen() allocates memory (typically via malloc()) for a FILE object, something like:

                // internally sets a buffer, a FILE structure (mostly)
                struct _IO_FILE {
                    int _fileno;        // actual kernel file descriptor
                    char * _buffer;     // in-memory buffer
                    size_t _bufsize;
                    size_t _pos;
                    int _flags;         // read/write/EOF/error flags
                    ...
                };

                //This structure lives in user space — meaning it's managed entirely by the C runtime, not the kernel.

    IMP part:-  (c) System call delegation
                Now the library calls the OS-level system call open():
                int fd = open("data.txt", O_RDONLY);    //O_RDONLY → read-only mode, in open syscall.

                // This transitions the control from user mode to the kernel mode via a trap instruction

                
            2. In the OS:
                
                (a) Path resolution
                Finds the inode representing "data.txt".

                (b) permission checking
                If permissions are okay, continue; otherwise, return -1 with errno = EACCES.

                (c) updates table of "open files"   //File object creation in kernel memory
                
                        -> A pointer to the file’s inode (the on-disk metadata).
                        -> A current file offset.
                        -> File access flags. :-
                            +-------------------+
                            | Kernel File Table |
                            +-------------------+
                            | fd=3 → inode#1357 |
                            | offset = 0        |
                            | mode = read-only  |
                            | ref_count = 1     |
                            +-------------------+

                (d) File descriptor assignment

                The kernel adds an entry to the process file descriptor table (per-process structure).

                    Example:

                    fd 0 → stdin
                    fd 1 → stdout
                    fd 2 → stderr
                    fd 3 → data.txt
            
                    open() returns this integer descriptor (e.g., 3) to the user space.


            3. Back in the C library

                The returned descriptor 3 is stored inside the FILE struct’s _fileno field.
                The library sets up an I/O buffer in memory for efficient reading/writing (e.g., 4KB).
                Finally, fopen() returns a pointer to the fully initialized FILE struct i.e.:
                    
                    FILE *fp → points to user-space FILE struct
                    fp->_fileno = 3
                    fp->_buffer = malloc(4096)
                    
                // So fp is not a kernel object — it’s a C library abstraction layered on top of a real file descriptor inside the OS.


            4. Reading/writing operations
                
                // Read
                Eg- char c = fgetc(fp);

                First time => gets a chunck of data from file to a buffer,
                i.e.    fgetc() checks if the user-space buffer has data.
                        If not, it calls read(fp->_fileno, buffer, 4096) → another system call.
                        Kernel copies 4KB of data from disk (via disk cache → RAM → user buffer).
                        Buffer now has data, and fgetc() returns one byte from it.
                This buffering minimizes syscall overhead — one read() fetches many characters.
                
                //write
                Eg- fwrite():
                Data is stored in the buffer (stored until full) and, fflush()/fclose() forces a write() syscall.

            5. Close operation

                Eg- fclose(fp);
                
                Flushes any unwritten buffered data (write() syscall).
                Calls the kernel close(fd) → kernel decrements the reference count in its open file table.
                If refcount → 0, kernel releases the inode reference.
                Frees user-space FILE structure and buffer.


            Cursor management-

            at kernel level- Each open file has exactly one “master cursor” (offset) maintained by the OS kernel,   // inside per-open-file table entry
            at program level- each FILE* stream in user space has a private “buffer pointer” tracking where it is within its buffer.    // libc, inside FILE* struct in user space
            replenish buffer-
                if (_pos < _bufsize)
                    just return buffer[_pos++].
                else
                    load next chunck of buffer by syscall.
            no more char to read (end of file)- EOF.
            kernel- Reads up to BUFSIZE bytes from disk into kernel page cache, then copies to user-space buffer.
                    Advances the kernel cursor by number of bytes actually read.
            
            How putc() works internally (write side)
                Eg-
                    putc('x', file_ptr);
                        (a) Write to buffer
                            libc writes 'x' into the user-space buffer:
                                fp->_buffer[fp->_pos++] = 'x';
                            As long as buffer not full, no system call yet — data stays in user RAM.
                        (b) When buffer fills or flushed
                            If _pos == _bufsize, or if fflush()/fclose() is called:
                                1. libc issues:
                                    write(fp->_fileno, fp->_buffer, _pos);
                                2. Kernel writes these bytes to the file, starting at the kernel cursor.
                                3. Kernel advances the kernel file offset by _pos.
                                4. libc resets _pos = 0.


        END FOPEN EXPLAINATION
            */

# include <stdio.h>

int main(){
    // file_ptr is a ptr to a "FILE". ( FILE is not a structure, however, it is defined with a typedef)
    FILE *file_ptr = fopen("temp_3.txt", "r");  // pass 2 arguments, 1) a char ptr to the string of file_name. 2) type of file operations going to do.
    FILE *file_ptr_2 = fopen("temp_3.txt", "w");                                         // some systems also need you to specify (binary or text) the type of file opening by a prefix b, to r/w.
    
    // reading-
    char var = getc(file_ptr);  // getc returns a single character from the file. returns EOF in case error or if end of file was reached.
    putc('x', file_ptr);    // writes a single character into the file, returns the character written. Retuns EOF if error occurs.

    // when starting the C program, the OS is reponsible to open 3 imp files:- 1) stdin 2) stdout 3) stderr. (these files are opened and their file ptrs are stred withing these variable, from which, it is defined in stdio.h lib)
        // hence:
        # define getchar() getc(stdin)
        # define putchar(c) putc(c, stdout)


        //With formatted reading and writing:   (it is similar to usual printf and scanf, except that pass file_ptr as first argument.)
            char arr[100] = {0};
            fscanf(file_ptr, arr);
            fprintf(file_ptr_2, "Writing...\nFirst write.");

    fclose(file_ptr);   // this does the reverse of fopen, it breaks the connection between FILE * ptr and external name in file descriptor table of kernel of "open files".
                            // as for a particular program for some systems, the OS prevents multiple files from being open at the same time.
                                // also, while writing is done by putc, the speed of kept by first writing to a buffer, and when full/ external flush, the buffer is commited to memory of file.
                            // by default, when a program terminates the file is also closed. 

    return 0;
}
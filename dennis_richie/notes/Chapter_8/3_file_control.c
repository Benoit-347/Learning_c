// other than default input, ouput and stderr, that is open by shell, each time you run a program;
    // you need to explicitly open files in order to read or write them.
    // 2 sys calls for this: open and creat         ([sic] => a author's expression that the adjacent word is not a typo)


// int open(char * name, int flags, int perms);
// the first argument of open sys call is a ptr to char arr of filename.
// the second argument is "how the file is to be opened" i.e. reading only / writing only / reading and writing.
                                                            // O_RDONLY    / O_WRONLY     / O_RDWR
    // The write modes without the "O_TRUNC" flag will act like append, without overwriting existing data in the file.
// the third argument is perms, here for open it will always be 0 (as the kernel ignores the perm argument for open sys call).
    // the open sys call can be used only on existing files. It is an error to use open() sys call on non existent files.
// for Non-existent files we use the creat() sys call (modern times, we use the O_CREAT flag at open syscall)
    // creat(name, perms)   creat makes a new file, if exists it truncates i.e. acts like open() sys call with O_TRUNC flag
    // open(name, O_WRONLY | O_CREAT, 0644);    // append if exists, else creat.
    // open(name, O_WRONLY | O_CREAT | O_TRUNC);    // delete old data and write from start of file, create new file is file does not exist.


// PERMS
// the UNIX system uses 9 bits for permission information for read(), write() and execute() access;
    // there are 3 categories: 1. owner of the file, 2. owner's group, (and everone else) 3. others.
        // the perms denote 3 bits for each category.

/*
| Category | r  | w  | x    | Binary bits | Octal value |
| -------- | -- | -- | -    | ----------- | ----------- |
| Owner    | ✔️ | ✔️ | ❌   | `110`       | `6`         |
| Group    | ✔️ | ❌ | ❌   | `100`       | `4`         |
| Others   | ✔️ | ❌ | ❌   | `100`       | `4`         |
*/
// hence perm to only write would be bit value 010, == 2    read, write and execute would be 111, == 7

// UNIX program cp, that copies one file to another.
    // our version cannot access directories, and it also does not inherit permissions, but invents them.

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

# define PERMS 0b111111111 // equivalent to read 1, write 1, execute 1 * 3 times; for owner, developer and others category.

int main(int argc, char * argv[]){
    int f1, f2, n;
    char buf[BUFSIZ];

    if (argc != 3)
        error("Usage: cp from to");
    if ( (f1 = open(argv[1], O_RDONLY, 0)) == -1 ) 
        error("cp: can't open %s", argv[1]);
    if ( (f2 = creat(argv[2], PERMS)) == -1 )
        error("cp: can't create %s, mode %03o", argv[2], PERMS);
    
    while ( (n = read(f1, buf, BUFSIZ)) > 0 )
        if (write(f2, buf, n) != n)
            error("cp: write error on file %s", argv[2]);
    
    return 0;
}

// running cmd:
    // gcc     3_file_control.c    -o     temp.exe;    ./temp.exe  1_file_descriptors.c    hello.txt
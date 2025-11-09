// input and output uses read() and write() sys calls, where 1st argument is the file descriptor, 2nd arg is the char ptr from where data is read or written to, 3rd arg is number of bytes transferred.
    // int n_read = read(int fd, char *buf, int n);
    // int n_written = write(int fd, char * buf, int n);
// each of these calls returns the count of number of bytes transferred. (edge cases- 0 => end of file, -1 => error of some sort)

// syscalls.h has a new lib unistd.h
// #include <unistd.h>  (unix std.h)     // for read(), write(), close(), lseek()
// #include <fcntl.h>  (file control.h)  // for open(), O_RDONLY, O_WRONLY, etc. (not needed here, but common)
// #include <sys/types.h>  // for ssize_t, off_t (optional)
// # include <stdio.h> // already defines BUFSIZ and EOF
// using all this knowledge, we can write a simple program to copy the data from anything to anything (stdin to stdout), since stdin and stdout can be redirected to any file or device.

# include <unistd.h>
# include <stdio.h> // already defines BUFSIZ and EOF

int main(){
    char buf[BUFSIZ];
    int n;

    while ( (n = read(0, buf, BUFSIZ)) > 0 )
        write(1, buf, n);
    
    return 0;
}

// unbuffered version of getch

int getchar(void){
    char c;
    return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;     // return c on sucess, return EOF on end of file or error.
}

// buffered version:
// 1. read a chunk if buffer is empty by read(0, arr_buf, 1024)     2. every getch obtains the char from arr_buf, with a ptr keeping track of last getch ptr on arr_buf.

int getchar(void){
    static char buf[BUFSIZ];
    static char * bufp = buf;
    static int n = 0;

    if (n == 0){
        n = read(0, buf, BUFSIZ);   // there are moments where input only recieves some number of characters, like typing "hello" and pressing \n, to keep track of how many chars we have recieved, instead of assuming the full buffer was filled, The return feature is very useful.
        bufp = buf;     // reset pointer to start of buffer on read sys call.
    }

    // if n is 0 even after reading, --n will provide -1.
        // this buffered input, is what causes the property that, getch only returns EOF when the first char of input is EOF, (i.e., the first read got EOF)
    return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}
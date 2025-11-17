// a whole program to perform file-read and write operations, using only sys calls and code instructions (no library).

// has 5 parts to program, part 5 ends with creating struct to store file descriptor of stdin, stdout and stderr.
    /*
    part-1: create general FILE struct to store desciptors, setup fns to flush to in and out buffer, setup putc and getc.
    part-2: create fopen fn.
    part-3: create flush fn for in  (read)
    part-4: "     >same<    "   out (write)
    part-5: _iob is storage and patform for all files; _iob handles the max 20 file desciptors.

            _iob
            // it is a arr of FILE structs, and also first 3 elements are #defined to use stdin stdout and stderr;
                // the _iob is initializes first 3 elements to setup for ( stdin,out,err) use.
    */

// need to implement automatic flushing before program ends.

// PART 1
#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 // max #files open at once

// creating the FILE struct, for using on all files opened.
// a sttuct that contains base pos, cur pos, remaining size, file_access mode, file descriptor.

typedef struct _iobuf {     
    int cnt; // shows how much of space left in buffer (for putc, in stdout; ) (stdin, it denots how many chars left to consume) (but, count = max_space - cnt (cnt = free space left))
    char *ptr; // next character position 
    char *base; // location of buffer
    int flag; // mode of file access 
    int fd; // file descriptor 
} FILE;
extern FILE _iob[OPEN_MAX];

// will be opened at PART 5,    part-5 already sets up values to 0 to the members. (this starts the file management, by _iob keeping all files)
// this is a file; 1st struct FILE out of 20 file desciptor elements.
# define stdin   (&_iob[0]) // this is a buffer, to which, elements are removed, then pulled when empty (sys call reads data and fulls)
# define stdout  (&_iob[1]) // even this buffer, elements added, thn flushed when full  (sys call writes and empties data)
# define stderr  (&_iob[2])

enum _flags {
    _READ = 01,     // file open for reading
    _WRITE = 02,    // file open for writing 
    _UNBUF = 04,    // file is unbuffered 
    _EOF = 010,     // EOF has occurred on this file *
    _ERR = 020      // error occurred on this file 
};

    // for below fn body, see part 3 and 4
int _fillbuf(FILE *);   // If the count goes negative, however, getc calls the function _fillbuf to replenish the buffer, re-initialize the structure contents, and return a character.
int _flushbuf(int, FILE *); // calling a function _flushbuf when its buffer is full.

# define feof(p)     (((p)->flag & _EOF) != 0)  // p is a ptr to the _iobuf struct
# define ferror(p)   (((p)->flag & _ERR) != 0)
# define fileno(p)   ((p)->fd)

            // putc and getc uses buffers as (read from buf) (characters to write buf), adds a char to buff in write each putc; adds ptr in read buff to show getc, uses cnt to denote when 0 ele left. putc uses cnt to show buff is full.
                    // if there is atleast 1 char within buff (has -- prefix, so condition- '>=0' )
                    // cnt = no of chars left to consume from prior read
# define getc(p)    (--(p)->cnt >= 0 ? (unsigned char) *(p)-> ptr++ : _fillbuf(p))  // obtain 1 char from _iobuf,   inside struct, add 1 to ptr after returning [ptr]. 
                    // cnt = space left in buff
# define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))   // here notice the '=' operator, 
// putc and getc uses different buffers here. Writing to stdout- increase ptr in buff of (to write to stdout) after adding one item to the to write buf
                                            // |||ly            increase ptr in buff (to read from stdin) after a read op.

# define getchar() getc(stdin)
# define putchar(x) putc((x), stdout)

// fopen()
// Most of fopen is concerned with getting the file opened and positioned at the right place, and setting the flag bits to indicate the proper state.
// fopen does not allocate any buffer space; this is done by _fillbuf when the file is first read.

// PART 2
#include <fcntl.h>
#include <unistd.h>
#define PERMS 0b111110110 // RW for owner, group, others */
FILE *fopen(char *name, char *mode){
    int fd;
    FILE *fp;   // ptr to _iobuf

    // skip program if improper mode
    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;

    // need to store a file (here in FILE _iob[20]), when opened, to store we need a free slot in the 20 max limit of open files
    // finding free slot to open file
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ( (fp->flag & (_READ | _WRITE)) == 0)
            break;  // found free slot
    // if all for loops used up (hence not 'break' over-incr loop var)-
    if (fp >= _iob + OPEN_MAX)
        return NULL;    // no free slots found.

    // opening file, and w.r.t. to mode.
    // options: create with (name, perms) 2. open if exists (name, 0_WRONLY, 0) else- create with (name, perms) if not exist and lseek to end of file 3. open (name, O_RDONLY, 0)
        
    if (*mode == 'w')       
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        fd = open(name, O_WRONLY, 0);
        if ((fd) == -1)
            fd = creat(name, PERMS);    // the next line lseek is redundant here
        else
            lseek(fd, 0L, 2);
    }
    else
        fd = open(name, O_RDONLY, 0);

    // after opening file, setting up the struct storing file descriptors, with 
        /*
        1. assign file descriptor to FILE struct
        2. initialize count to 0,
        3. keep base pos of file cursor to 0
        4. assign wither read or write mode (_READ OR _WRITE)
        */

    if (fd == -1)
        return NULL;    // couldn't access name
    fp->fd = fd;    // assign to member fd, var fd
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}


// PART 3
# include <stdlib.h>
// _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp){
    int bufsize;

    // check flag if it is incorrect (this is a buff for read)
    if ((fp->flag) != _READ)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    
    // if no buffer yet
    if (fp->base == NULL)
        // if can't get buffer
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;

    fp->ptr = fp->base; // initialize ptr, to start pos
    fp->cnt = read(fp->fd, fp->ptr, bufsize);   // perform the read operation, return no of char read to count.
    
    // add debugg info, if cnt is -1, change flag to EOF, else change flag to error.
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
        fp->cnt = 0;    // change count back to 0, then exit fn with EOF.
        return EOF;
    }

    // if all works well,
    return (unsigned char) *fp->ptr++;
}


// PART 4 (using gpt)

int _flushbuf(int c, FILE *fp)
{
    int bufsize;

    /* Must be writable */
    if ((fp->flag & _WRITE) == 0)
        return EOF;

    /* Determine buffer size */
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

    /* Allocate buffer if needed */
    if (fp->base == NULL) {
        fp->base = (char *) malloc(bufsize);
        if (fp->base == NULL) {      /* Can't allocate */
            fp->flag |= _ERR;
            return EOF;
        }
        fp->ptr = fp->base;
        fp->cnt = bufsize;
    }

    /* Write buffer to file BEFORE adding new char */
    int n = fp->ptr - fp->base;      // bytes currently in buffer

    if (n > 0) {
        if (write(fp->fd, fp->base, n) != n) {
            fp->flag |= _ERR;
            fp->cnt = 0;
            return EOF;
        }
    }

    /* Reset buffer */
    fp->ptr = fp->base;
    fp->cnt = bufsize - 1;

    /* Store new character into buffer */
    *fp->ptr++ = (char) c;

    return (unsigned char)c;
}



// PART 5
// how everything gets started. The array _iob must be defined and initialized
FILE _iob[OPEN_MAX] = { // intializing the structs in struct arr.
    // stdin, stdout, stderr
    { 0, (char *) 0, (char *) 0, _READ, 0 },
    { 0, (char *) 0, (char *) 0, _WRITE, 1 },
    { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};



int main(){
    FILE * fp_1 = fopen("hello_world.txt", "w");
    char arr[1000];
    int max = 26;
    int j;
    for (int i = 0; i<1000; i++){
        j = i%26;
        putc('a'+j, fp_1);
        if (j == 25)
            putc('\n', fp_1);
    }

    _flushbuf(EOF, fp_1);
}
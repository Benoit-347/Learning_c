#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 // max #files open at once

typedef struct _iobuf {     // a buffer that contains base pos, cur pos, remaining size, file_access mode, file descriptor.
int cnt; // characters left
char *ptr; // next character position 
char *base; // location of buffer
int flag; // mode of file access 
int fd; // file descriptor 
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])

enum _flags {
_READ = 01,     // file open for reading
_WRITE = 02,    // file open for writing 
_UNBUF = 04,    // file is unbuffered 
_EOF = 010,     // EOF has occurred on this file *
_ERR = 020      // error occurred on this file 
};

int _fillbuf(FILE *);   // If the count goes negative, however, getc calls the function _fillbuf to replenish the buffer, re−initialize the structure contents, and return a character.
int _flushbuf(int, FILE *); // calling a function _flushbuf when its buffer is full.

#define feof(p)     (((p)->flag & _EOF) != 0)
#define ferror(p)   (((p)->flag & _ERR) != 0)
#define fileno(p)   ((p)->fd)

# define getc(p)    (--(p)->cnt >= 0 ? (unsigned char) *(p)-> ptr++ : _fillbuf(p))  // ( if count has remaining, go to ptr in struct p, then add 1 to ptr, then derefrence it and return this) else _fillbuf(p). 
# define putc(x, p) (--(p)-> cnt >=0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

# define getchar() getc(stdin)
# define putchar(x) putc((x), stdout)

// fopen()
// Most of fopen is concerned with getting the file opened and positioned at the right place, and setting the flag bits to indicate the proper state.
// fopen does not allocate any buffer space; this is done by _fillbuf when the file is first read.

#include <fcntl.h>
#include <unistd.h>
#define PERMS 0b110110110 // RW for owner, group, others */
FILE *fopen(char *name, char *mode){
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ( (fp->flag & (_READ | _WRITE)) == 0)
            break;  // found free slot
    if (fp >= _iob + OPEN_MAX)
        return NULL;    // no free slots found.

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    }
    else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1)
        return NULL;    // couldn't access name
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}

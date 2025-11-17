===============================================================================
B.1  INPUT / OUTPUT  —  <stdio.h>
===============================================================================
Overview
  - A "stream" is a source or sink of data; examples: files, terminals, pipes.
  - Streams can be text (sequence of lines ending with '\n') or binary (sequence of bytes).
  - Opening a file returns a FILE*; closing it breaks the association.
  - Three standard streams opened at program start:
      stdin  - standard input
      stdout - standard output
      stderr - standard error (usually unbuffered)
  - Important: text vs binary matters on platforms that translate newline representation.
sql
Copy code
File open/close and tmp names
  FILE *fopen(const char *filename, const char *mode)
    - mode examples:
       "r"   : read text
       "w"   : write text (truncate/create)
       "a"   : append text (open/create, write at end)
       "r+"  : read/update
       "w+"  : read/update (truncate/create)
       "a+"  : read/update (append on writes)
       add 'b' for binary: "rb", "w+b", ...
    - If mode includes update (r+/w+/a+), you MUST fflush() or fseek()/ftell() between a read and a write.
    - Returns NULL on failure. Check errno or use perror().

  FILE *freopen(const char *filename, const char *mode, FILE *stream)
    - Reassociates an existing stream (often stdin/stdout/stderr) with a file.
    - Useful for redirection in simple programs.

  int fclose(FILE *stream)
    - flushes output, frees buffers, closes OS descriptor
    - returns 0 on success, EOF on error

  int fflush(FILE *stream)
    - flush buffered output to device; fflush(NULL) flushes all output streams
    - undefined on input streams (unless implementation documents otherwise)

  int remove(const char *filename)  — delete file
  int rename(const char *old, const char *new)  — rename file

  FILE *tmpfile(void)
    - opens a temporary file in "wb+" mode that is removed automatically on close or program exit

  char *tmpnam(char s[L_tmpnam])
    - generates a (unique) filename string but does NOT create the file; unsafe for race conditions
pgsql
Copy code
Buffering control
  int setvbuf(FILE *stream, char *buf, int mode, size_t size)
    - mode: _IOFBF (full buffering), _IOLBF (line buffering), _IONBF (no buffering)
    - call BEFORE performing I/O on stream
    - if buf != NULL, use provided buffer; otherwise library allocates
    - returns non-zero on failure

  void setbuf(FILE *stream, char *buf)
    - shorthand: setbuf(stream, NULL) disables buffering
    - setbuf(stream, buf)  ≈ setvbuf(stream, buf, _IOFBF, BUFSIZ)
csharp
Copy code
Formatted output (printf family)
  - int fprintf(FILE *stream, const char *fmt, ...);
  - int printf(const char *fmt, ...);       /* fprintf(stdout, ...) */
  - int sprintf(char *s, const char *fmt, ...); /* writes into s; beware buffer overflow */
  - int snprintf(char *s, size_t n, const char *fmt, ...); /* safe form */

  - vprintf / vfprintf / vsprintf take a va_list (used for wrappers).

  Format specifiers components:
    %[flags][width][.precision][length]conversion

    flags: -, +, (space), 0, #
    width: number or '*'
    precision: .number or .*
    length: h, l, L  (h: short; l: long; L: long double)
    conversion: d,i,u,o,x,X,e,E,f,g,G,c,s,p,n,%

  Common pitfalls:
    - Use snprintf to avoid buffer overflow.
    - For floating printing, precision controls digits after decimal for %f, or significance for %g.
    - %n writes the number of characters printed so far into an int* — dangerous if misused; do not use with untrusted format strings.
csharp
Copy code
Formatted input (scanf family)
  - int fscanf(FILE *stream, const char *fmt, ...);
  - int scanf(const char *fmt, ...);          /* fscanf(stdin, ...) */
  - int sscanf(const char *s, const char *fmt, ...); /* input from string */

  Format pieces: conversion specifications similar to printf but:
    - whitespace in format eats any amount of whitespace in input (including newline)
    - ordinary characters in format must match input exactly (ignoring whitespace effects)
    - '*' suppresses assignment (e.g., "%*s" reads an item but does not store it)
    - width may be specified to prevent buffer overflow (e.g., "%99s")
    - conversion %[...] set scans a bracketed set

  Returns number of items converted and assigned, or EOF on error/before conversion.

  Pitfalls:
    - scanf reads across line boundaries (white space includes '\n').
    - ALWAYS specify width for %s to avoid buffer overrun.
    - Using scanf for input parsing can be brittle: prefer fgets() + parse (sscanf/strtol) for robust input handling.
pgsql
Copy code
Character I/O helpers
  /* These may be macros for speed; macros can evaluate arguments multiple times! */
  int fgetc(FILE *stream)   /* returns int (unsigned char) or EOF */
  int getc(FILE *stream)    /* may be macro */
  int getchar(void)         /* getc(stdin) */

  int fputc(int c, FILE *stream)
  int putc(int c, FILE *stream)   /* may be macro */
  int putchar(int c)              /* putc(c, stdout) */

  char *fgets(char *s, int n, FILE *stream)
    - reads at most n-1 chars, stops at newline (newline is kept), terminates with '\0'
  char *gets(char *s)   /* UNSAFE: no length check — do not use in new code */

  int puts(const char *s)  /* writes s and newline; returns non-negative or EOF */

  int ungetc(int c, FILE *stream)
    - pushes one character back on stream (guaranteed at least one)
    - return c on success, EOF on error
vbnet
Copy code
Block I/O (binary)
  size_t fread(void *ptr, size_t size, size_t nobj, FILE *stream)
    - reads up to nobj objects of 'size' bytes, returns number actually read
  size_t fwrite(const void *ptr, size_t size, size_t nobj, FILE *stream)
    - writes up to nobj objects, returns number successfully written

  Use cases:
    - efficient binary read/write of arrays/structures
    - check return value to detect partial read/write (e.g., EOF or error)
    - after fread/fwrite check feof() / ferror()
pgsql
Copy code
File positioning
  int fseek(FILE *stream, long offset, int origin)
    - origin: SEEK_SET, SEEK_CUR, SEEK_END
    - for text streams only offsets returned by ftell are portable; nonzero offsets for text are implementation-defined

  long ftell(FILE *stream)  — current file position (or -1L on error)
  void rewind(FILE *stream) — fseek(stream, 0L, SEEK_SET); clearerr(stream);

  int fgetpos(FILE *stream, fpos_t *pos)
  int fsetpos(FILE *stream, const fpos_t *pos)
    - fpos_t is opaque type suitable for fsetpos/fgetpos
java
Copy code
Error detection
  void clearerr(FILE *stream)
  int feof(FILE *stream)   /* non-zero if EOF indicator set */
  int ferror(FILE *stream) /* non-zero if error indicator set */
  void perror(const char *s) /* prints s: strerror(errno) */
  extern int errno; /* set on system/library errors; use strerror(errno) for message */
pgsql
Copy code
Buffering visual (simplified)
  FILE structure (conceptual):
   +----------------+
   | buffer base    | <--- malloc-ed or user-supplied
   | buffer ptr     | <-- next char in/from buffer
   | cnt            | <-- chars available (read) or space left (write)
   | flags          | <-- read/write/error/unbuffered/EOF
   | file descriptor| <-- OS FD
   +----------------+

  read flow:  read() fills buffer -> cnt = bytes_read -> getc/ fgetc use buffer until cnt==0 -> _fillbuf called
  write flow: buffer collects out chars -> cnt decremented -> when full -> _flushbuf writes out then reset
cpp
Copy code
===============================================================================
B.2  CHARACTER CLASS TESTS  —  <ctype.h>
===============================================================================
  - int isalpha(int c), isdigit, isalnum, isspace, isupper, islower, ispunct, isprint, isgraph, iscntrl, isxdigit
  - functions take int which is EOF or representable as unsigned char
  - toupper(int c) / tolower(int c)
  - return non-zero if true, zero otherwise

Pitfalls:
  - Passing plain char to these on platforms where char is signed may produce negative values; cast to (unsigned char) first.
    e.g., isalpha((unsigned char)c)
rust
Copy code
===============================================================================
B.3  STRING FUNCTIONS  —  <string.h>
===============================================================================
Two groups:
  - str* functions for NUL-terminated strings
  - mem* functions for raw memory

Common functions:
  strcpy/strncpy, strcat/strncat
  strcmp/strncmp
  strchr/strrchr
  strstr
  strlen
  strtok (stateful tokenization; not reentrant)
  strerror(int errnum) -> textual error message

mem functions:
  memcpy(dest, src, n)   /* do NOT overlap */
  memmove(dest, src, n)  /* supports overlapping regions */
  memset(ptr, c, n)
  memcmp
  memchr

Pitfalls:
  - strncpy does NOT guarantee NUL-termination if source length >= n. Always ensure termination.
  - strtok uses static state; use strtok_r for reentrancy.
  - treat strings as unsigned char for comparisons when byte values >127 matter.
===============================================================================
B.4  MATH  —  <math.h>
===============================================================================
Key functions:
  trig: sin, cos, tan, asin, acos, atan, atan2
  exp/log: exp, log, log10, pow, sqrt
  rounding: floor, ceil
  abs: fabs
  frexp / ldexp: split/compose mantissa/exponent
  modf: split integral and fractional parts
  fmod: floating remainder

Errors and errno:
  - EDOM: domain error (argument out of domain)
  - ERANGE: range error (overflow/underflow)
  - HUGE_VAL returned for overflow with sign, errno = ERANGE

Pitfalls:
  - Use isnan/isinf macros if needed (C99).
  - pow(0, non-positive) or pow(negative, non-integer) domain issues.
csharp
Copy code
===============================================================================
B.5  UTILITY / GENERAL  —  <stdlib.h>
===============================================================================
Numeric conversion:
  atof, atoi, atol  — convenience wrappers; prefer strtod/strtol for error detection
  strtod(const char *s, char **endp)
  strtol(const char *s, char **endp, int base)
  strtoul

Random:
  int rand(void)          /* 0..RAND_MAX */
  void srand(unsigned seed)

Memory management:
  void *malloc(size_t n)
  void *calloc(size_t nobj, size_t size)  /* zero-initialized */
  void *realloc(void *p, size_t size)
  void free(void *p)

Process control / exit:
  void abort(void)        /* abnormal termination */
  void exit(int status)   /* normal termination; calls registered atexit() */
  int atexit(void (*f)(void)) /* register fn to run at normal termination */

Environment and execution:
  int system(const char *cmd) /* execute command interpreter — unsafe with untrusted strings */
  char *getenv(const char *name)

Searching / sorting:
  void *bsearch(const void *key, const void *base, size_t n, size_t size,
                int (*cmp)(const void *key, const void *elem));
  void qsort(void *base, size_t n, size_t size,
             int (*cmp)(const void *a, const void *b));

Misc:
  abs, labs, div, ldiv

Pitfalls & notes:
  - malloc/realloc/calloc return NULL on failure; always check.
  - free(NULL) is safe (no-op).
  - realloc(NULL, size) behaves like malloc(size).
  - Use qsort/bsearch with a correctly implemented comparator; comparator must follow strict weak ordering.
  - srand(1) gives deterministic pseudo-random sequence; seed with time(NULL) for nondeterministic.
pgsql
Copy code
===============================================================================
B.6  DIAGNOSTICS  —  <assert.h>
===============================================================================
  - assert(expression) prints message and calls abort() if expression is false.
  - compile-time disabling: define NDEBUG before including <assert.h> to remove asserts (zero-cost).
  - useful for internal sanity checks, not for run-time recoverable errors.
pgsql
Copy code
===============================================================================
B.7  VARIABLE ARGUMENT LISTS  —  <stdarg.h>
===============================================================================
  - va_list ap; va_start(ap, last_named_arg); use va_arg(ap, type); va_end(ap)
  - Use vprintf/vfprintf/vsnprintf when writing wrapper functions that forward varargs
  - Always ensure matching types (promotions occur: float->double, char/short -> int)
  - Wrong va_arg type ⇒ undefined behavior (UB)
sql
Copy code
===============================================================================
B.8  NON-LOCAL JUMPS  —  <setjmp.h>
===============================================================================
  - jmp_buf env; int val = setjmp(env);
    - setjmp returns 0 initially, nonzero when longjmp jumps back
  - longjmp(env, val) resumes at the corresponding setjmp with return value val (or 1 if val==0)
  - Caveats:
    - Do NOT longjmp into a function that has already returned.
    - Automatic (stack) variables that are not volatile may have unspecified values after longjmp (if modified after setjmp). Mark variables volatile if needed.
    - setjmp/longjmp bypass normal stack unwinding (no C++ destructors called).
java
Copy code
===============================================================================
B.9  SIGNALS  —  <signal.h>
===============================================================================
  - void (*signal(int sig, void (*handler)(int)))(int)
    - set handler for signal sig
    - handler can be SIG_DFL (default), SIG_IGN (ignore), or a function pointer
  - int raise(int sig) — send signal to current process

  Common signals:
    SIGFPE  - arithmetic error (divide by zero, overflow)
    SIGILL  - illegal instruction
    SIGINT  - interactive interrupt (Ctrl-C)
    SIGSEGV - segmentation violation (invalid memory access)
    SIGTERM - termination request

  Caveats:
    - Only async-signal-safe functions are allowed inside signal handlers (see POSIX list); most stdio functions are NOT safe.
    - signal() semantics vary historically; prefer sigaction() on POSIX for reliable behavior.
perl
Copy code
===============================================================================
B.10  DATE & TIME  —  <time.h>
===============================================================================
Types:
  time_t, clock_t, struct tm

Functions:
  clock()        — CPU time used by program
  time(time_t *t) — current calendar time (seconds since epoch)
  double difftime(time_t t2, time_t t1)
  mktime(struct tm *tm) — convert local time struct to time_t
  asctime(const struct tm *tm), ctime(const time_t *t) — convert to string (useful, but not thread-safe)
  gmtime/localtime — convert time_t to UTC/local struct tm (return pointer to static data; not thread-safe)
  strftime — format struct tm into a buffer according to format specifiers

strftime specifiers:
  %A %a %B %b %c %d %H %I %j %m %M %p %S %U %W %x %X %y %Y %Z %%

Pitfalls:
  - gmtime/localtime return pointers to internal static buf; use gmtime_r/localtime_r for reentrancy (POSIX).
  - asctime/ctime are not thread-safe (use asctime_r/ctime_r if available).
pgsql
Copy code
===============================================================================
B.11  IMPLEMENTATION LIMITS  —  <limits.h> & <float.h>
===============================================================================
  - limits.h defines integer type limits (INT_MAX, INT_MIN, LONG_MAX, etc.)
  - float.h defines minimum/maximum values and precision for floating types
  - Use these macros for portable numeric bounds and for checking overflows
sql
Copy code
===============================================================================
PRACTICAL TIPS & COMMON PITFALLS (summary)
===============================================================================
  - Check return values! (fopen, malloc, fread, fwrite, realloc, system, etc.)
  - For IO:
      * Prefer fgets + sscanf/strtol/strtod over scanf for robust input parsing.
      * Use snprintf instead of sprintf to avoid buffer overflow.
      * Remember to fflush(stdout) when you need flushed output (or use line-buffering/ unbuffered).
  - For memory:
      * free every malloc/calloc/realloc that you own. free(NULL) is safe.
      * realloc can return NULL — preserve original pointer until you confirm reallocation success.
  - For varargs:
      * Watch integer promotions; wrong type in va_arg = UB.
  - For signals:
      * Keep handlers short and only call async-signal-safe functions.
  - For multi-threaded programs (POSIX):
      * Many C standard functions are not thread-safe or use static storage (e.g., strtok, ctime); use the _r reentrant variants when available.
  - Use errno + perror() or strerror(errno) for diagnosing system-level failures.
sql
Copy code
ASCII DIAGRAMS (quick mental models)
===============================================================================
1) FILE buffering model (write):
   app calls putc/printf -> data goes into buffer at ptr -> cnt-- 
   when cnt==0 -> library calls write(fd, base, BUFSIZ) -> reset ptr/cnt

   [ FILE object ]
   base ---> [ buffer bytes ...................... ]
             ^      ^            ^
             |      |            |
             ptr----+            end pointer
             cnt (remaining free slots)

2) fread/fwrite memory layout:
   ptr -> [ obj0 ][ obj1 ][ obj2 ] ...
   fread(ptr, size, n, stream) reads up to n objects; returns number read (not bytes)

3) printf format anatomy:
   % [flags] [width] [.precision] [length] conversion
   example: "%-07.2lf"  => '-' left-adjust, '0' pad zeros, width 7, precision 2, length l (double), f (fixed)

4) setjmp/longjmp flow:
   setjmp(env)  -- saves register/stack state --> returns 0
   ... deeper calls ...
   longjmp(env, val) -- restores state saved and makes setjmp(...) return val (non-zero)
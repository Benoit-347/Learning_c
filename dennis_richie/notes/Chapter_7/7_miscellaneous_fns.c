# include <stdio.h>


// 1. string
# include <string.h>

//restrict is a imp keyword for optimisation-
    // restrict gives the compiler the heads up that the pointed location is only pointed to by 1 pointer, hence allowig for aggresive optimization.    The compiler can keep the data in memory until the 1 pointer changes the value.
                                                                                                        // else,the compiler must now frequently Reload data from memory, in case another pointer has changed it (a phenomenon called aliasing). 

// to the end of ptr s1, append the chars from s2.
char *strcat(char * restrict s1, const char * restrict s2);

// to the end of ptr s1, append the chars from s2, and copies only n number of chars from s2.    (if copy pasting 1 char is 1 count, max number of times is n chars that will be copied.)
char *strncat(char * restrict s1, const char * restrict s2, size_t n);

// compares chars from left to right for s1 against s2; return negative, zero, or positive for s < t, s == t, s > t */
int strcmp(const char *s1, const char *s2);

// same as strcmp, but only cmps first n chars. if still equal and beyond- then returns 0, as equal until tht point, and does not even consider the remaining
int strncmp(const char *s1, const char *s2, size_t n);

// copies all chars, char for char from t to s
char *strcpy(char * restrict s1, const char * restrict s2);

// copies all chars, char for char from t to s, at most n characters (of t).
char *strncpy(char * restrict s1, const char * restrict s2, size_t n);

//return length of s
size_t strlen(const char *s);

/* strchr(s,c) return pointer to first c in s, or NULL if not present */
char *strchr(const char *s, int c);

/* strrchr(s,c) return pointer to last c in s, or NULL if not present */
char *strrchr(const char *s, int c);


// 2. ctype
# include <ctype.h>

// they use lookup tables and explicit type casting, unlike the below code, beware.

// returns non-zero if c is upper case, 0 if not upper
#define isupper(c)  ((c) >= 'A' && (c) <= 'Z')

// returns non-zero if c is lower case, 0 if not lower
#define islower(c)  ((c) >= 'a' && (c) <= 'z')

// returns non-zero if c is digit, 0 if not digit
#define isdigit(c)  ((c) >= '0' && (c) <= '9')

// returns  non-zero if isalpha(c) or isdigit(c), 0 if not ( alphabet || decimal )
#define isalnum(c)  (isupper(c) || islower(c) || isdigit(c))

// returns non-zero if c is blank, tab, newline, return, formfeed, vertical tab
#define isspace(c)  ((c) == ' ' || (c) == '\t' || (c) == '\n' || \
                     (c) == '\r' || (c) == '\f' || (c) == '\v')

// returns a char, converted to upper case
#define toupper(c)  ((c) >= 'a' && (c) <= 'z' ? ((c) - 'a' + 'A') : (c))

// returns a char, converted to lower case
#define tolower(c)  ((c) >= 'A' && (c) <= 'Z' ? ((c) - 'A' + 'a') : (c))


// 3. malloc => allocate single block && uninitialized, calloc => allocates mutiple blocks && initialized to 0 , free => free only frees up allocation tht was done by malloc and calloc (kept track by header at allocation).
                                                                // (whr the min size of a unit block is determined by the "element size" argument passed)

// 4. math.h
# include <math.h>

// cosine of x, x in radians
double cos(double x);

// atan(ratio) i.e. ratio = y/x
    // therefore we have atan2(y, x) i.e. atan(y/x).

// (tan^-1) arctangent of y/x, in radians
double atan2(double y, double x);

// exponential function e^x
double exp(double x);

// natural log: (base e) (x > 0)
double log(double x);

// common log- (base 10) (x > 0)
double log10(double x);

// x^y
double pow(double x, double y);

// quare root of x (x > 0)
double sqrt(double x);

// absolute value of x
double fabs(double x);


// 5. stdlib
# include <stdlib.h>

// rand() generates a pseudo-random integer in the range [0, RAND_MAX]
int rand(void);

// srand(seed) initializes the pseudo-random number generator using the given seed
void srand(unsigned int seed);

// stdlib also provides ungetc (for our ungetch).

//list of all stdlib fns:

// calloc(n, size) allocate space for n objects of size size and initialize to zero
void *calloc(size_t nmemb, size_t size);

// malloc(size) allocate space for an object of size size
void *malloc(size_t size);

// realloc(p, size) change size of object pointed to by p to size
void *realloc(void *ptr, size_t size);

// free(p) free space pointed to by p
void free(void *ptr);

// abort() terminates program abnormally
void abort(void);

// exit(status) terminates program normally with exit status
void exit(int status);

// getenv(name) returns pointer to value of environment variable name
char *getenv(const char *name);

// running commands to the terminal through the program execution:
    // system("data");      it also returns, the output status back (which is system dependent). (in UNIX the same status that is returned by exit(), is returned by system() )

// system(s) execute command in string s
int system(const char *command);

// qsort(base, n, size, cmp) sorts array base of n members, each of size size, using comparison function cmp
void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

// bsearch(key, base, n, size, cmp) search array base for key using binary search
void *bsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

// the below fns are also part of stdlib and do operations on a char arr (string):

// convert string (that is a number in string format) to the number, either ato- 1. float (f) 2. integer (i) 3. long int (l).
    // atof(s) convert string s to double
    double atof(const char *s);

    // atoi(s) convert string s to integer
    int atoi(const char *s);

    // atol(s) convert string s to long integer
    long int atol(const char *s);

// also convert string (that is a number in string format) to the number, either 1. double (d) 2. long (l) 3. unsigned long (ul).
    // But, BENEFIT: they also keep track of first non-number element in the char arr, by writing tht ptr to 3rd arg (here, endptr).
        // They perform a robust FSM parse similar to the ato- group to achieve this fast.

    // strtod(s, endp) convert string s to double, storing pointer to remainder in *endp
    double strtod(const char * restrict nptr, char ** restrict endptr);

    // strtol(s, endp, base) convert string s to long, storing pointer to remainder in *endp and using specified number base
    long int strtol(const char * restrict nptr, char ** restrict endptr, int base);

    // strtoul(s, endp, base) convert string s to unsigned long, storing pointer to remainder in *endp and using specified number base
    unsigned long int strtoul(const char * restrict nptr, char ** restrict endptr, int base);


int main(){
    char s[] = "hello world";
    printf("String length: %d\n", strlen(s));
    system("date");
    // system("sudo shutdown"); lmao    
    // can use pipelining,  part 1- with a scipt wrting to stdout the password (like a program giving out a output) by command "echo",  part 2- ask program to read password from stdout (by taking input to stdin (usually takes from here), from the stdout)  by using pipeline "|"     part 3. use -S flag prefix as However, sudo is hardcoded to bypass stdin for password prompts., and takes directly from terminal device.
                                                                                                                                                                                // "|" takes the Standard Output (stdout) of echo and redirects it to the Standard Input (stdin)            
    // hence:
        // system("echo <password> | sudo shutdown")
    system("sudo apt update");
}